// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
	
protected:

public:
	UAuraAttributeSet();

	//the function to register replicate variable
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//character/Enemy's current health
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;

	//this macro make 4 function here(include set/init/get health)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	
	//character/Enemy's MaxHealth
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;

	//this macro make 4 function here(include set/init/get Maxhealth)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);

	//character/Enemy's current mana
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	
	//this macro make 4 function here(include set/init/get Mana)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);

	//character/Enemy's MaxMana
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;

	//this macro make 4 function here(include set/init/get Mana)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);

	//the function call on the client when Health change on server
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//the function call on the client when MaxHealth change on server
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//the function call on the client when Mana change on server
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//the function call on the client when MaxMana change on server
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
