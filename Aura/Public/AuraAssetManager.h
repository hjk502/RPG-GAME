// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

private:

protected:

	//call when ue Asset start initial
	virtual void StartInitialLoading() override;
	
public:
	static UAuraAssetManager& Get();
};
