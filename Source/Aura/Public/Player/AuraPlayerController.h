// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController(); //构造函数

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="输入")
	TObjectPtr<UInputMappingContext> AuraContext;//玩家输入上下文
};
