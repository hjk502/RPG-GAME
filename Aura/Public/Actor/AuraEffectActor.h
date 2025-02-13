// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
private:
	
protected:

	//Instantly Game Effect
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;

	//the policy of InstanceEffect Apply
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	EEffectApplicationPolicy InstanceEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	
	//Duration Game Effect
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	//the policy of DurationEffect Apply
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;

	//Infinite Game Effect
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	//the policy of InfiniteEffect Apply
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;

	//the policy of InfiniteEffect Remove
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	EEffectRemovePolicy InfiniteEffectRemovePolicy=EEffectRemovePolicy::RemoveOnEndOverlap;

	//store the ActiveGameplayEffectHandle mapping relative with overlap actor's AbilitySystemComponent
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*>  ActiveEffectHandles;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	bool bDestroyOnEffectRemoval=false;
	
	//apply effect actor's effect to the character
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
};
