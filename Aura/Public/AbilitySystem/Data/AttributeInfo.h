// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


//this struct about the message show on the attribute menu
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag=FGameplayTag();

	//attribute name on the menu
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName=FText();

	//attribute Description on the menu
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription=FText();

	//attribute value on the menu
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue=0.0f;
};

/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
private:

protected:

public:

	//the array to store the information show in the attribute menu
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;

	//search attribute info about this Tag
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag,bool bLogNotFound=false)const;
};
