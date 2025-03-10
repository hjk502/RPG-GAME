// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

private:

	//the game ability that character has at start
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//the character's weapon Mesh
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//the Base AbilitySystemComponent
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//the Base AttributeSet
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//the class of gameEffect to initialized the primary Attributes value
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<class UGameplayEffect> DefaultPrimaryAttributes;

	//the class of gameEffect to initialized the secondary Attributes value(when primary Attributes value change it will auto change)
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<class UGameplayEffect> DefaultSecondaryAttributes;

	//the class of gameEffect to initialized the Vital Attributes value(when primary Attributes value change it will auto change)
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<class UGameplayEffect> DefaultVitalAttributes;

	//apply the effect(that Set primary/secondary attributes) to self
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass,float Level) const;

	//initialized primary/secondary default attributes value
	void InitializeDefaultAttriutes() const;

	virtual void InitAbilityActorInfo();

	//add the character's ability
	void AddCharacterAbilities();
	
public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet(){return AttributeSet;}
};
