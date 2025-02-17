// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//the character's weapon Mesh
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//the Base AbilitySystemComponent
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//the Base AttributeSet
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//the class of gameEffect to initialized the default Attributes value
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<class UGameplayEffect> DefaultPrimaryAttributes;

	//initial character/enemy 's default attributes value
	void InitializePrimaryAttributes() const;

	virtual void InitAbilityActorInfo();
	
public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet(){return AttributeSet;}
};
