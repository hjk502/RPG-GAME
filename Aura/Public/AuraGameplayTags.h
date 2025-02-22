// Fill out your copyright notice in the Description page of Project Settings.
//this class to sign GamePlayTags

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

    static const FAuraGameplayTags& Get(){return GameplayTags;}
	
	static void InitializeNativeGameplayTags();
};
