// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//when the GameplayEffect(include instance and ) Applied to Self(then call function)
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{

	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for(const FGameplayTag& Tag:TagContainer)
	{
		//TODO: BoardCast the tag to widget controller
		const FString Msg=FString::Printf(TEXT("GE Tag: %s"),*Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,Msg);
		
	}
	
}
