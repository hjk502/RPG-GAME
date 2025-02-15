// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()

private:

protected:

	virtual void BeginPlay() override;

	//set the ability component's OwnerActor and AvatarActor(connect component with character)
	virtual void InitAbilityActorInfo() override;
	
public:

	AAuraEnemy();
	
	//interface of HighlightActor in AuraEnemy
	virtual void HighlightActor() override;

	//interface of HighlightActor in Aura
	virtual void UnHighlightActor() override;
};
