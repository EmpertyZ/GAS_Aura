// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
/**
 * 
 */
//创建动态多播委托,FOnHPChangeSignature委托代理类,NewHP委托参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChangeSignature, float, NewHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHPChangeSignature, float, NewMaxHP);

//MP委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMPChangeSignature, float, NewMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMPChangeSignature, float, NewMaxMP);

UCLASS(BlueprintType, Blueprintable)//标记BlueprintType和Blueprintable使该类可以在蓝图中使用
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	//广播初始化值
	virtual void BroadcastInitValue() override;
	//绑定回调依赖项，在数据更新时调用方法里面绑定的委托，实现数据更新
	virtual void BindCallbackToDependencies() override;
	
	//声明生命委托类
	UPROPERTY(BlueprintAssignable, Category = "GAS_Attribute")//BlueprintAssignable只能用于组播委托，相当于定义了蓝图可调用的组播委托
	FOnHPChangeSignature OnHPChangeSignature;
	UPROPERTY(BlueprintAssignable, Category = "GAS_Attribute")
	FOnMaxHPChangeSignature OnMaxHPChangeSignature;
	//声明MP委托类
	UPROPERTY(BlueprintAssignable, Category = "GAS_Attribute")
	FOnMPChangeSignature OnMPChangeSignature;
	UPROPERTY(BlueprintAssignable, Category = "GAS_Attribute")
	FOnMPChangeSignature OnMaxMPChangeSignature;
	
protected:
	//相应改变属性委托的方法
	void HPChange(const FOnAttributeChangeData& Data) const;
	void MaxHPChange(const FOnAttributeChangeData& Data) const;
	void MPChange(const FOnAttributeChangeData& Data) const;
	void MaxMPChange(const FOnAttributeChangeData& Data) const;
	
	
};
