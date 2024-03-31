// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraActor::AAuraActor()
{
 	//游戏开始时不需要启用tick
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());//将球形碰撞检测绑定在根组件上
	

}

// Called when the game starts or when spawned
void AAuraActor::BeginPlay()
{
	Super::BeginPlay();
	
	//在球体上绑定重叠事件委托,添加动态委托，相当于蓝图中的调用事件分发
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraActor::EndOverlap);
}

void AAuraActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))/*获取所重叠的actor所实现的接口*/
	{	//从AbilitySystemComponent()获取AuraAttributeSet
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		//测试使用，后面需要更改
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);//const_cast强制转换,不推荐使用
		MutableAuraAttributeSet->SetHealth(MutableAuraAttributeSet->GetHealth() + 25.f);//重叠后增加25生命值
		MutableAuraAttributeSet->SetMana(MutableAuraAttributeSet->GetMana() - 20.f);//重叠后减20蓝
		Destroy();//碰到后销毁该对象
	}
	
}

void AAuraActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


