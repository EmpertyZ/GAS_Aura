// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//开启网络复制
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//检测光标追踪
	CursorTrace();
}
//检测光标追踪
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorResult;
	GetHitResultUnderCursor(ECC_Visibility, false,  CursorResult);
	//判断光标追踪是否被阻挡
	if (!CursorResult.bBlockingHit) return;

	//记录上次命中的actor
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorResult.GetActor());
	
	/**
	 * 光标跟踪时出现的情况：
	 *	1.LastActor和ThisActor都为null
	 *		-不做处理
	 *	2.LastActor is null，ThisActor is valid
	 *		-highlight ThisActor
	 *	3.LastActor is valid，ThisActor is null
	 *		-UnHighlight LastActor
	 *	4.LastActor is valid，ThisActor is valid，and LastActor == ThisActor
	 *		-不做处理
	 *	5.LastActor is valid，ThisActor is valid，but LastActor != ThisActor
	 *		-UnHighlight LastActor，Highlight ThisActor
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			//情况1：-不做处理
		}
		else
		{
			//情况2：-highlight ThisActor
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//情况3：-UnHighlight LastActor
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor == ThisActor)
			{
				//情况4：-不做处理
				
			}
			//情况5：-UnHighlight LastActor，Highlight ThisActor
			LastActor ->UnHighlightActor();
			ThisActor ->HighlightActor();
		}
	}
	
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
	//check(Subsystem);//使用
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);//添加上下文映射
	}
	

	bShowMouseCursor = true;//显示鼠标光标
	DefaultMouseCursor = EMouseCursor::Default;//设置默认鼠标光标图形

	FInputModeGameAndUI InputModeData;//用于设置游戏输入和UI输入模式
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置鼠标不越过viewport
	InputModeData.SetHideCursorDuringCapture(false);//设置鼠标按下时不隐藏鼠标
	SetInputMode(InputModeData);//设置所设置好的输入模式
}

//设置输入组件,用于自定义输入绑定
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//转换且获取增强输入组件，CastChecked相当于cast加check
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//绑定输入动作
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw,0.f);//初始化YawRotation
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);//获取向前向量
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);//获取向左向量

	if(APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


