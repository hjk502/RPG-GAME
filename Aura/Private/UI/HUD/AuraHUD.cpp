// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "UI/WidgetController/AttributeMenuWidgetController.h"

/////////////////////////////////////////////////////////////////
/// AuraHUD OverlayWidget system
/////////////////////////////////////////////////////////////////

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController==nullptr)
	{
		OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);

		//the overlayController need 4 parameter(playerState and so on) to know the message from Module(here use MMC module)
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		//bind the function call when the attributes change
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized,please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class uninitialized,please fill out BP_AuraHUD"));

	//create overlay widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget=Cast<UAuraUserWidget>(Widget);

	//link the Overlay widget controller with the overlay widget
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController=GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);

	//board Initial value
	WidgetController->BroadcastInitialValue();
	
	Widget->AddToViewport();
}

/////////////////////////////////////////////////////////////////
/// AuraHUD AttributeMenuWidget system
/////////////////////////////////////////////////////////////////

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributeMenuWidgetController==nullptr)
	{
		AttributeMenuWidgetController=NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);

		//the AttributeMenuController need 4 parameter(playerState and so on) to know the message from Module(here use MMC module)
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);

		AttributeMenuWidgetController->BindCallbacksToDependencies();
		
	}

	return AttributeMenuWidgetController;
}