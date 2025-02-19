// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency=100.f;

	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	//the gameplay effect replicate rule
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

/////////////////////////////////////////////////////////////////
/// AuraPlayerState Replicate system 
/////////////////////////////////////////////////////////////////

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState,Level);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	
}

/////////////////////////////////////////////////////////////////
/// AuraPlayerState AbilitySystemComponent system 
/////////////////////////////////////////////////////////////////

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}




