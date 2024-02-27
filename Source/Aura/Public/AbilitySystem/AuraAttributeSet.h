// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAuraAttributeSet, Health) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health)

#define ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAuraAttributeSet, MaxHealth) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth)

#define ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAuraAttributeSet, MaxHealth) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth)

#define ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAuraAttributeSet, Mana) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Mana) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana)

#define ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAuraAttributeSet, MaxMana) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxMana) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxMana) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxMana)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//构造函数
	UAuraAttributeSet();
	//重写GetLifetimeReplicatedProps，将需要复制的Properties（属性）添加到复制列表里
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "角色基础属性")
	FGameplayAttributeData Health;//复制（预测）属性：血量
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);//该宏用于访问和初始化属性：血量
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "角色基础属性")
	FGameplayAttributeData MaxHealth;//复制（预测）属性：最大生命值
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);//该宏用于访问和初始化属性：最大血量

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "角色基础属性")
	FGameplayAttributeData Mana;//复制（预测）属性：法力值
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);//该宏用于访问和初始化属性：法力值

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "角色基础属性")
	FGameplayAttributeData MaxMana;//复制（预测）属性：最大法力值
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);//该宏用于访问和初始化属性：最大法力值

	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;//在方法后添加const，不能改变参数变量
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};


