// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//为服务器初始化actor信息
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//为客户端初始化actor信息
	InitAbilityActorInfo();
}

//初始化actor信息方法
void AAuraCharacter::InitAbilityActorInfo()
{
	//获取PlayerState
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	//从PlayerState获取AbilitySystemComponent
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	//从PlayerState获取AttributeSet
	AttributeSet = AuraPlayerState->GetAttributeSet();
	//从AbilitySystemComponent设置InitAbilityActorInfo，InOwnerActor设置为AuraPlayerState，InAvatarActor设置为该类
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
}


