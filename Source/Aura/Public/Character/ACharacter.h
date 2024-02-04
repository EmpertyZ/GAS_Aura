// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

UCLASS(Abstract)//Abstract 说明符会将类声明为"抽象基类"，阻止用户向关卡中添加此类的Actor。对于单独存在时没有意义的类，此说明符非常有用
class AURA_API AACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
