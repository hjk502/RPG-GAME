// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
private:
	
	//character current level
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level)
	int32 Level=1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	
protected:

	//the AbilitySystemComponent in AuraPlayerState
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//the AttributeSet in AuraPlayerState
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	
public:

	AAuraPlayerState();

	//the function to register replicate variable
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//get the AbilitySystemComponent in AuraPlayerState
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//get the AttributeSet in AuraPlayerState
	UAttributeSet* GetAttributeSet(){return AttributeSet;}

	//get the character's level store in the PlayerState
	FORCEINLINE int32 GetPlayerLevel() const{return Level;}
};
