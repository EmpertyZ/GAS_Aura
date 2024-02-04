// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ACharacter.h"

// Sets default values
AACharacter::AACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AACharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


