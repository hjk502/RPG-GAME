// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
		
}

void UAttributeMenuWidgetController::BroadcastInitialValue()
{
	UAuraAttributeSet* AS=CastChecked<UAuraAttributeSet>(AttributeSet);

	//broadcast
	check(AttributeInfo);
	FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attribute_Primary_Strength);
	Info.AttributeValue=AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
	
	
}
