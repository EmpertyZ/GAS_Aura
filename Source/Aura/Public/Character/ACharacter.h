// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ACharacter.generated.h"
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)//Abstract 说明符会将类声明为"抽象基类"，阻止用户向关卡中添加此类的Actor。对于单独存在时没有意义的类，此说明符非常有用
class AURA_API AACharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();
	//用于申明类中的成员函数为“只读”函数，即函数后面加了const之后该函数不能改变类的数据成员
	//重写AbilitySystemInterface方法
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="战斗")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//创建存放AbilityComponent和AttributeSet的指针
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
