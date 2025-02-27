// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h" 
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
private:

	
protected:

public:

	template<class UserClass,typename PressedFuncType,typename ReleasedFuncType,typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig,UserClass* Object,PressedFuncType PressedFunc,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	//the asset store Input
	check(InputConfig);

	for(const FAuraInputAction& Action:InputConfig->AbilityInputActions)
	{
		if(Action.InputAction&&Action.InputTag.IsValid())
		{
			//if this action need Press to trigger once,then this case
			if(PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}

			//if the action need Stop press trigger once,then this case
			if(ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			
			//if this action need Held pressKey to active ,then this case
			if(HeldFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);	
			}
			
		}
	}
}
