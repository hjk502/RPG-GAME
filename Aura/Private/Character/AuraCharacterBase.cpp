// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

/////////////////////////////////////////////////////////////////
/// AuraCharacterBase AbilitySystemComponent system 
/////////////////////////////////////////////////////////////////

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

/////////////////////////////////////////////////////////////////
/// AuraCharacterBase initial ASC system 
/////////////////////////////////////////////////////////////////

void AAuraCharacterBase::InitAbilityActorInfo()
{
	
}

/////////////////////////////////////////////////////////////////
/// AuraCharacterBase Set primary/secondary Attributes value 
/////////////////////////////////////////////////////////////////

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GamePlayEffectClass);
	FGameplayEffectContextHandle ContextHandle=GetAbilitySystemComponent()->MakeEffectContext();

	ContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle SpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffectClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent()); 
}

/////////////////////////////////////////////////////////////////
/// AuraCharacterBase Initial primary/secondary Attributes value 
/////////////////////////////////////////////////////////////////

void AAuraCharacterBase::InitializeDefaultAttriutes() const
{
	//effect current value,infinite gameplayEffect
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.0f);
	ApplyEffectToSelf(DefaultVitalAttributes,1.0f);
}

/////////////////////////////////////////////////////////////////
/// AuraCharacterBase AbilitySystem 
/////////////////////////////////////////////////////////////////

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC=CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority()){return;}
	
	AuraASC->AddCharacterAbilities(StartupAbilities);
	
}
