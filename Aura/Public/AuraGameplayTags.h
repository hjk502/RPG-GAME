// Fill out your copyright notice in the Description page of Project Settings.
//this class to sign GamePlayTags and store all tags(use for access thees tags in the C++)

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  AuraGameplayTags
 *
 *  Singleton containing native gameplay Tags
 */

struct FAuraGameplayTags
{
private:
	static FAuraGameplayTags GameplayTags;
 
protected:
    
public:

	//get the GameTags assemble
    static const FAuraGameplayTags& Get(){return GameplayTags;}

	//initial the GameTags assemble
	static void InitializeNativeGameplayTags();


	/**
	 * the primary attribute gamePlay Tags
	 */
	
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;
	

	/**
	 * the second attribute gamePlay Tags
	 */
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;


	/**
	 * the Input Action gamePlay Tags
	 */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	
};
