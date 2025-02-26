// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);	
	}

	//set the mouse cursor could show(mouse type default)
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	//the mouse will not just in viewport
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//mouse cursor will not hide after be capture by the viewport
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

/////////////////////////////////////////////////////////////////
/// AuraPlayerController handle input system 
/////////////////////////////////////////////////////////////////

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);
	
	//ETriggerEvent::Triggered mean it is happening,AAuraPlayerController::Move will store the value
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
	
	if(APawn* ControllerPawn=GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

/////////////////////////////////////////////////////////////////
/// AuraPlayerController mouse cursor system 
/////////////////////////////////////////////////////////////////

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	
	if(!CursorHit.bBlockingHit){return;}

	//check if the interface is implemented
	LastActor=ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * Line Trace from cursor .There are several scenarios
	 *  A. LastActor is null && ThisActor is null
	 *		- Do nothing.
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is Valid && ThisActor is null
	 *		- UnHighlight Last Actor
	 *	D. Both actors are valid ,but LastActor !=ThisActor
	 *		-UnHighlight LastActor ,and Highlight This Actor
	 *	E. Both actors are Valid, and are the same actor
	 *		-Do nothing
	 */

	if(LastActor==nullptr)
	{
		if(ThisActor!=nullptr)
		{
			//Case B
			ThisActor->HighlightActor();
		}
		else
		{
			//Case A -both are null,do nothing
		}
	}
	else //Last Actor is Valid
	{
		if(ThisActor==nullptr)
		{
			//Case C - UnHighlight Last Actor
			LastActor->UnHighlightActor();
		}
		else //both actors are valid
		{
			if(LastActor!=ThisActor)
			{
				//Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//Case E -do nothing
			}
		}
	}
	
}