// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "Interaction/CombatInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	//capture the Vigor from Game effect Target to calculate
	IntDef.AttributeToCapture=UAuraAttributeSet::GetIntelligenceAttribute();
	IntDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	IntDef.bSnapshot=false;

	//the Tarry to store the capture Attributes
	RelevantAttributesToCapture.Add(IntDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTag=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag=Spec.CapturedTargetTags.GetAggregatedTags();

	//store tags
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTag;
	EvaluateParameters.TargetTags=TargetTag;

	//capture the vigor
	float Int=0.f;
	GetCapturedAttributeMagnitude(IntDef,Spec,EvaluateParameters,Int);
	Int=FMath::Max<float>(Int,0.f);

	//get the auraCharacter's level
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel=CombatInterface->GetPlayerLevel();

	return 50.f+2.5f*Int+15.f*PlayerLevel;
}
