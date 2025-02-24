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

	//broadCast the Strength value on the attribute menu
	check(AttributeInfo);

	for(auto& Pair:AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(Pair.Key);

		//get the attribute current value from this attribute
		Info.AttributeValue=Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
		
	}
	
}
