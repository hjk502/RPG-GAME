// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

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

	//thing do when cursor trace on it
    void CursorTrace();

	//test the actor if implemented interface
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	
protected:
	virtual void BeginPlay() override;
	
	//player controller input component
	virtual void SetupInputComponent() override;

	//player move action
	void Move(const FInputActionValue& InputActionValue);
public:

	
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
};
