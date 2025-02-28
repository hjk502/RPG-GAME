// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
private:

	
	
protected:

	
public:

	//the default tag that the ability have
	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTag StartupInputTag;
};
