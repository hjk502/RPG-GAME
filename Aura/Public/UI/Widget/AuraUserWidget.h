// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:

protected:
	
	//widget get the data from this controller
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
public:

	//the controller widget get the data from
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	//set the controller that connect with this widget
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
};
