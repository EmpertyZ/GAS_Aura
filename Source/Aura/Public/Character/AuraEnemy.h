// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ACharacter.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	/** 重写怪物接口里的高亮方法 */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** end 重写怪物接口里的高亮方法 */
	
protected:
	
	virtual void BeginPlay() override;
};
