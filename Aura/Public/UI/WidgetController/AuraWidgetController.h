// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
private:
	
protected:

	//store playerController in this WidgetController
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<APlayerController> PlayerController;

	//store playerState in this WidgetController
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<APlayerState> PlayerState;

	//store AbilitySystemComponent in this WidgetController
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//store AttributeSet in this WidgetController
	UPROPERTY(BlueprintReadOnly,Category="Widget Controller")
	TObjectPtr<UAttributeSet> AttributeSet;
	
public:
};
