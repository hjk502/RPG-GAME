// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);

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
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image=nullptr;
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
private:
	
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Wdiget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	//return the DataTable's row
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
	
	//when Health change,call widget controller to change it on HUD
	void HealthChanged(const FOnAttributeChangeData& Data) const;

	//when MaxHealth change,call widget controller to change it on HUD
	void MaxHealthChanged(const FOnAttributeChangeData& Data)const;

	//when Mana change,call widget controller to change it on HUD
	void ManaChanged(const FOnAttributeChangeData& Data)const;

	//when MaxMana change,call widget controller to change it on HUD
	void MaxManaChanged(const FOnAttributeChangeData& Data)const;
	
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

	//bind the function call when the mana change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	//bind the function call when the MaxMana change,Overlay will listen it and change variable on HUD
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
