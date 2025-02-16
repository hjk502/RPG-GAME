// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

//custom DataTable type(could show in the editor)
USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag=FGameplayTag();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message=FText();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image=nullptr;
};

//delegate declear

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature,float,NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
private:
	
protected:

	//the DataTable that 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Wdiget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	//return the DataTable's row
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
	
public:

	//boardCast initial value to widget bind with this controller
	virtual void BoardcastInitialValue() override;

	//bind the function call when the attributes change,Overlay will listen it and change variable on HUD
	virtual void BindCallbacksToDependencies() override;

	//bind the function call when the health change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	//bind the function call when the MaxHealth change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	//bind the function call when the mana change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	//bind the function call when the MaxMana change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	//
	UPROPERTY(BlueprintAssignable,Category="GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowSignature;
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
