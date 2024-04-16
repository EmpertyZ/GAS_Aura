// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraActor::AAuraActor()
{
 	//游戏开始时不需要启用tick
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AAuraActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	//从目标Actor的abilitySystem接口，获取GetAbilitySystemComponent
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	//检查获取的目标ASC和传入的变量是否为空
	if (TargetASC == nullptr) return;
	check(GamePlayEffectClass);

	//规范套路
	//创建EffectContext，其上下文返回的是一个句柄
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	//通过句柄添加产生效果的对象
	EffectContextHandle.AddSourceObject(this);
	//创建输出到外部的效果规范,返回的是一个句柄
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GamePlayEffectClass, 1.f, EffectContextHandle);
	//设置输出的效果作用给自身
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}




