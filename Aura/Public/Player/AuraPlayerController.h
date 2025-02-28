// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"


struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
private:

	//the enhance input 's Context
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	//the input action relative to input Context
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	//player move action
	void Move(const FInputActionValue& InputActionValue);
	
	//thing do when cursor trace on it
    void CursorTrace();

	//test the actor if implemented interface
	IEnemyInterface* LastActor=nullptr;
	IEnemyInterface* ThisActor=nullptr;

	/**
	 * Callback function that bind with UAuraInputComponent
	 */
	
	void AbilityInputTagPressed(FGameplayTag InputTag);

	void AbilityInputTagReleased(FGameplayTag InputTag);

	void AbilityInputTagHeld(FGameplayTag InputTag);

	//the DataAsset(the relatives between Tags and InputAction)
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	//store the AuraAbilitySystemComponent in AuraPlayerController
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	//get the AuraAbilitySystemComponent store in the AuraPlayerController
	UAuraAbilitySystemComponent* GetASC();

	/**
	 * AuraCharacter click to move
	 */

	//the Destination that character need to move
	FVector CachedDestination=FVector::ZeroVector;

	//the time that player press mouse left button to move
	float FollowTime=0.f;

	//if Follow Time less this Threshold,then judge it be short move
	float ShortPressThreshold=0.f;

	bool bAutoRunning=false;

	bool bTargeting=false;

	//if the character's distance with Destination less than this,then stop auto run
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius=50.f;

	//the spline 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
protected:
	virtual void BeginPlay() override;
	
	//player controller input component
	virtual void SetupInputComponent() override;

public:

	
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
};
