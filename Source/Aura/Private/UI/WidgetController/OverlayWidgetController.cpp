// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitValue()
{
	Super::BroadcastInitValue();

	//获取父类的attributeSet，通过attributeSet去获取属性
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHPChangeSignature.Broadcast(AuraAttributeSet->GetHealth());//广播设置初始生命值,相当于蓝图里的调用分发
	OnMaxHPChangeSignature.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnMPChangeSignature.Broadcast(AuraAttributeSet->GetMana());//广播设置初始蓝量
	OnMaxMPChangeSignature.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	Super::BindCallbackToDependencies();
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	//GetGameplayAttributeValueChangeDelegate方法在AttributeSet值改变的时候就会调用该委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HPChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHPChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::MPChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxMPChange);
	
}

void UOverlayWidgetController::HPChange(const FOnAttributeChangeData& Data) const
{
	//广播设置最新生命值
	OnHPChangeSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHPChange(const FOnAttributeChangeData& Data) const
{
	//广播设置最新最大生命值
	OnMaxHPChangeSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MPChange(const FOnAttributeChangeData& Data) const
{
	//广播设置最新蓝量
	OnMPChangeSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxMPChange(const FOnAttributeChangeData& Data) const
{
	//广播设置最新最大蓝量
	OnMaxMPChangeSignature.Broadcast(Data.NewValue);
}
