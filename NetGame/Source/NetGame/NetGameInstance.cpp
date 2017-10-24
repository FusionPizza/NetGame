// Fill out your copyright notice in the Description page of Project Settings.

#include "NetGameInstance.h"




UNetGameInstance::UNetGameInstance(const FObjectInitializer & ObjectInitializer) 
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UNetGameInstance::Init() 
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}