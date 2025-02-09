// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

/////////////////////////////////////////////////////////////////
/// AuraPlayerEnemy mouse highlight system 
/////////////////////////////////////////////////////////////////

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;
}
