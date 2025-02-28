// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//when the GameplayEffect(include instance and ) Applied to Self(then call function)
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{

	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//the callFunction bind this delegate will receive it
	EffectAssetTags.Broadcast(TagContainer);
	
}

/////////////////////////////////////////////////////////////////
/// AuraAbilitySystemComponent Character Ability assign System 
/////////////////////////////////////////////////////////////////

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec=FGameplayAbilitySpec(AbilityClass,1);

		///grant default tags to GamePlayAbility
		if(const UAuraGameplayAbility* AuraAbility=Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

/////////////////////////////////////////////////////////////////
/// AuraAbilitySystemComponent Character Ability active System 
/////////////////////////////////////////////////////////////////

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()){return;}

	//Traverse all actionable ability,and active it
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		//if this ability has this disorder tags,then active it
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//announce the input key has pressed to the abilitySpec
			AbilitySpecInputPressed(AbilitySpec);
			
			//if this ability is not active,then active it
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()){return;}

	//Traverse all actionable ability,and active it
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		//if this ability has this disorder tags,then active it
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//announce the input key has released to the abilitySpec
			AbilitySpecInputReleased(AbilitySpec);
			
		}
	}
}
