// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer& /*store Asset Tags*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
private:
	
protected:

	//when the GameplayEffect(include instance and ) Applied to Self(then call function)
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
public:

	//initial aura ASC
	void AbilityActorInfoSet();

	//
	FEffectAssetTags EffectAssetTags;

	//abilitySystemComponent add the ability to character
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	//
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);
};
