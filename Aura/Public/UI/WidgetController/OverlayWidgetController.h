// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
private:
	
protected:

	//when abilitySystemComponent influence the Health,call widget controller to change it on HUD
	void HealthChanged(const FOnAttributeChangeData& Data) const;

	//when abilitySystemComponent influence the MaxHealth,call widget controller to change it on HUD
	void MaxHealthChanged(const FOnAttributeChangeData& Data)const;
	
public:

	//boardCast initial value to widget bind with this controller
	virtual void BoardcastInitialValue() override;

	//bind the function call when the attributes change,Overlay will listen it and change variable on HUD
	virtual void BindCallbacksToDependencies() override;

	//bind the function call when the health change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	//bind the function call when the MaxHealth change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
};
