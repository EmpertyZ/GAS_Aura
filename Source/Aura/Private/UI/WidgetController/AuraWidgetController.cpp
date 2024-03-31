// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& NewParam)
{
	PlayerController = NewParam.PlayerController;
	PlayerState = NewParam.PlayerState;
	AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(NewParam.AbilitySystemComponent);
	AttributeSet = Cast<UAuraAttributeSet>(NewParam.AttributeSet);
}

void UAuraWidgetController::BroadcastInitValue()
{
}

void UAuraWidgetController::BindCallbackToDependencies()
{
}
