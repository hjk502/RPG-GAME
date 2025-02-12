// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere,Category="Effects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
};
