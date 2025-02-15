// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include "Aura/Aura.h"

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
}

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

/////////////////////////////////////////////////////////////////
/// AuraPlayerEnemy mouse highlight system 
/////////////////////////////////////////////////////////////////

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

/////////////////////////////////////////////////////////////////
/// AuraCharacter initial ASC system
/////////////////////////////////////////////////////////////////

void AAuraEnemy::InitAbilityActorInfo()
{
	//link the abilitySystemComponent with enemy
	AbilitySystemComponent->InitAbilityActorInfo(this,this);

	Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent())->AbilityActorInfoSet();
}