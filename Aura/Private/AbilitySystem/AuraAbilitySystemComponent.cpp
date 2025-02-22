// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//when the GameplayEffect(include instance and ) Applied to Self(then call function)
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGameplayTags& GameplayTags=FAuraGameplayTags::Get();

	
	GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Orange,FString::Printf(TEXT("Tags: %s"),*GameplayTags.Attributes_Secondary_Armor.ToString()));
	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{

	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//the callFunction bind this delegate will receive it
	EffectAssetTags.Broadcast(TagContainer);
	
}
