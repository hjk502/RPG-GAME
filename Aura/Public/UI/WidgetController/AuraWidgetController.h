// Fill out your copyright notice in the Description page of Project Settings.
//base widget controller

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){}

	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS)
	: PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController=nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState=nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent=nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet=nullptr;
};

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

	//set four store variable in WidgetController
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	
	virtual void BroadcastInitialValue();

	virtual void BindCallbacksToDependencies();
};
