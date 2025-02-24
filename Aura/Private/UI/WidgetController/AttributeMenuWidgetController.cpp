// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue=Attribute.GetNumericValue(AttributeSet);
	//broadCast the info if ASC change the Attribute
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS=CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	//Mapping tag to function GetAttribute()
	for(auto& Pair:AS->TagsToAttributes)
	{
		//bind to delegate let ASC monitor,if the Attribute change,then call bind function
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair,AS](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key,Pair.Value());
			}
	    );

		
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValue()
{
	UAuraAttributeSet* AS=CastChecked<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for(auto& Pair:AS->TagsToAttributes)
	{

		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
	
}
