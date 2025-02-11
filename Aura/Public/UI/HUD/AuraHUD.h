// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AuraHUD.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
private:

	//the class of overlayWidget on HUD
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
protected:

	
	virtual void BeginPlay() override;
	
public:

	//the widget on the HUD
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	
};
