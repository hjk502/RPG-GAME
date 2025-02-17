// Fill out your copyright notice in the Description page of Project Settings.
//GameEffect will know it By ASC
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

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	//the GameEffect's source ASC
	UPROPERTY()
	UAbilitySystemComponent* SourceASC=nullptr;

	//the GameEffect's Source actor
	UPROPERTY()
	AActor* SourceAvatarActor=nullptr;

	//the GameEffect's source controller
	UPROPERTY()
	AController* SourceController=nullptr;

	//the GameEffect's source character
	UPROPERTY()
	ACharacter* SourceCharacter=nullptr;

	//the GameEffect Target ASC
	UPROPERTY()
	UAbilitySystemComponent* TargetASC=nullptr;

	//the GameEffect target actor
	UPROPERTY()
	AActor* TargetAvatarActor=nullptr;

	//the GameEffect target's controller
	UPROPERTY()
	AController* TargetController=nullptr;

	//the GameEffect target character
	UPROPERTY()
	ACharacter* TargetCharacter=nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:

	//get the message about this GameEffect that influence the Properties
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props);
	
protected:

public:
	UAuraAttributeSet();

	//call before attributes value change(use for clamp attributes value)
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//the function to register replicate variable
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	/**
	 * Primary Attributes
	 */

	//character/Enemy's current strength
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="Primary Attributes")
	FGameplayAttributeData Strength;
	//this macro make 4 function here(include set/init/get Strength)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);
	
	//character/Enemy's current Intelligence
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence,Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	//this macro make 4 function here(include set/init/get Intelligence)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);

	//character/Enemy's current Resilience
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Resilience,Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	//this macro make 4 function here(include set/init/get Resilience)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience);

	//character/Enemy's current Vigor
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Vigor,Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	//this macro make 4 function here(include set/init/get Vigor)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);

	/**
	 *  Secondary Attributes
	 */

	//character/Enemy's Armor
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor,Category="Secondary Attributes")
	FGameplayAttributeData Armor;
	//this macro make 4 function here(include set/init/get Armor)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor);

	//character/Enemy's ArmorPenetration(ArmorPenetration is the chance that attack could bypass Armor)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorPenetration,Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	//this macro make 4 function here(include set/init/get ArmorPenetration)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);

	//character/Enemy's blockChance(BlockChance is the chance that Injury suffered could be decline to 1/2)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BlockChance,Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;
	//this macro make 4 function here(include set/init/get BlockChance)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);

	//character/Enemy's CriticalHitChance
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitChance,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	//this macro make 4 function here(include set/init/get CriticalHitChance)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance);

	//character/Enemy's CriticalHitDamage
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitDamage,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	//this macro make 4 function here(include set/init/get CriticalHitDamage)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage);

	//character/Enemy's CriticalHitResistance(the chance could resistance the Critical Hit)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitResistance,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	//this macro make 4 function here(include set/init/get CriticalHitResistance)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance);

	//character/Enemy's HealthRegeneration
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthRegeneration,Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	//this macro make 4 function here(include set/init/get HealthRegeneration)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration);

	//character/Enemy's ManaRegeneration
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ManaRegeneration,Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	//this macro make 4 function here(include set/init/get ManaRegeneration)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration);

	//character/Enemy's MaxHealth
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	//this macro make 4 function here(include set/init/get MaxHealth)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);

	//character/Enemy's MaxMana
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Secondary Attributes")
	FGameplayAttributeData MaxMana;
	//this macro make 4 function here(include set/init/get Mana)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	
	/**
	 * Vital Attributes
	 */
	
	//character/Enemy's current health
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	//this macro make 4 function here(include set/init/get health)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);

	//character/Enemy's current mana
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	//this macro make 4 function here(include set/init/get Mana)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);


	/**
	 * OnRep function
	 */

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

	//the function call on the client when Strength change on server
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	//the function call on the client when Intelligence change on server
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	//the function call on the client when Resilience change on server
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	//the function call on the client when Vigor change on server
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	//the function call on the client when Armor change on server
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	//the function call on the client when ArmorPenetration change on server
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	//the function call on the client when BlockChance change on server
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	//the function call on the client when CriticalHitChance change on server
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	//the function call on the client when CriticalHitDamage change on server
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	//the function call on the client when CriticalHitResistance change on server
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	
	//the function call on the client when HealthRegeneration change on server
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	//the function call on the client when ManaRegeneration change on server
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
};
