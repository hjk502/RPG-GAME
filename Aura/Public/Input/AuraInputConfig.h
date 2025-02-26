// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

//link the ability active action with gamePlay Tags
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction=nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag=FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

private:

protected:

public:

	//store the link the ability active action with gamePlay Tags
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;

	//find the input action by GameplayTags
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag InputTag,bool bLogNotFound=false) const;
};
