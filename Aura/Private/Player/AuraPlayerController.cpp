// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "Components/SplineComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	//create spline component
	Spline=CreateDefaultSubobject<USplineComponent>("Spline");

	
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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent=CastChecked<UAuraInputComponent>(InputComponent);
	
	//ETriggerEvent::Triggered mean it is happening,AAuraPlayerController::Move will store the value
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);

	//if the
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

/////////////////////////////////////////////////////////////////
/// AuraPlayerController handle input(Move) system 
/////////////////////////////////////////////////////////////////

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
/// AuraPlayerController handle input(Ability Active) system 
/////////////////////////////////////////////////////////////////

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if(AuraAbilitySystemComponent==nullptr)
	{
		AuraAbilitySystemComponent=Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{

	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting=ThisActor?true:false;
		bAutoRunning=false;

		
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{

	if(GetASC()==nullptr){return;}
	
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{

	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}


	/**
	 * handle mouse left button held
	 */
	
	
	//if the character held left Mouse button and target enemy,then active ability
	if(bTargeting)
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else //in this case,aura character is held click left mouse button to move
	{
		FollowTime+=GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if(GetHitResultUnderCursor(ECC_Visibility,false,Hit))
		{
			CachedDestination=Hit.ImpactPoint;
		}

		if(APawn* ControlledPawn=GetPawn())
		{
			const FVector WorldDirection=(CachedDestination-ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
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