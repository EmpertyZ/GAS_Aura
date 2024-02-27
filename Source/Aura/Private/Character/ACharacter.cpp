// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ACharacter.h"

// Sets default values
AACharacter::AACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");//创建character下名字为weapon的子组件
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));//将改组件附加到weaponhandsocket
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//设置碰撞为无碰撞

	
}

UAbilitySystemComponent* AACharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AACharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


