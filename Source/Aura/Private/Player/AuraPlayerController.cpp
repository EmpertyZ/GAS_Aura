// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

AAuraPlayerController::AAuraPlayerController()
{
	//开启网络复制
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

/*
 * 添加增强输入
 */
	check(AuraContext);//上下文
	//获取本地玩家,获取子系统下的增强输入系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);//添加上下文映射

	bShowMouseCursor = true;//显示鼠标光标
	DefaultMouseCursor = EMouseCursor::Default;//设置默认鼠标光标图形

	FInputModeGameAndUI InputModeData;//用于设置游戏输入和UI输入模式
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置鼠标不越过viewport
	InputModeData.SetHideCursorDuringCapture(false);//设置鼠标按下时不隐藏鼠标
	SetInputMode(InputModeData);//设置所设置好的输入模式
}
