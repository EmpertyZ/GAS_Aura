// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;


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
	//设置输入组件,用于自定义输入绑定
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="输入")
	TObjectPtr<UInputMappingContext> AuraContext;//玩家输入上下文

	UPROPERTY(EditAnywhere, Category="输入")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};
