// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

/////////////////////////////////////////////////////////////////
/// UI variable Initial system 
/////////////////////////////////////////////////////////////////

void UOverlayWidgetController::BoardcastInitialValue()
{
	const UAuraAttributeSet* AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);

	//boardCast health and MaxHealth to widget
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

/////////////////////////////////////////////////////////////////
/// UI variable change system 
/////////////////////////////////////////////////////////////////

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);

	//bind to delegate let ASC monitor,if the Attribute change,then call bind function
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	//bind to delegate let ASC monitor,if the Attribute change,then call bind function
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	//bind to delegate let ASC monitor,if the Attribute change,then call bind function
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	//bind to delegate let ASC monitor,if the Attribute change,then call bind function
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	//bind the delegate,receive the effect tags
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag& Tag:AssetTags)
			{

				//For example, say that Tag = Message.HealthPotion
				//"Message. HealthPotion". MatchesTag("Message") will return True, "Message". MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag=FGameplayTag::RequestGameplayTag(FName("Message"));

				//if the Tag belong to Message
				if(Tag.MatchesTag(MessageTag))
				{
					//get the DataTable's row by tag
					const FUIWidgetRow* Row=GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
					
					//boardCast this row to all widget bind with delegate
					MessageWidgetRowSignature.Broadcast(*Row);
				}
			}
		}
	);
}
