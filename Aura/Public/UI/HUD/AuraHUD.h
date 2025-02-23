// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
private:

	//the widget on the HUD
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	//the class of overlayWidget on HUD
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	//the controller to control data in overlayWidget
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	//the widget class of OverlayWidgetController
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	
protected:

	
public:

	//get the OverlayWidget Controller link with overlay widget
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	//initial and put the overlay on HUD
	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);

	//get the AttributeMenuWidget Controller link with attribute menu
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	
};
