// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

//单例函数，当所需返回值为空时，重新创建一个新的
//该方法用于更新UI属性，
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		//OverlayWidgetController为空，重新创建新的，然后将传入的新的结构体值赋值给新的controller
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		//这里是一个回调广播
		//绑定回调依赖项，在数据更新时调用方法里面绑定的委托，实现UI数据更新
		OverlayWidgetController->BindCallbackToDependencies();
		
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidget没有传入，需要在蓝图里设置"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetController没有传入，需要蓝图内添加"));
	
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(UserWidget);
	
	//声明OverlayWidgetController的结构体并赋予初值
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);

	//广播初始值
	WidgetController->BroadcastInitValue();
	
	UserWidget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

}
