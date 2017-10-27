// Fill out your copyright notice in the Description page of Project Settings.

#include "NetGameInstance.h"

#include "Engine/Engine.h"



UNetGameInstance::UNetGameInstance(const FObjectInitializer & ObjectInitializer) 
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UNetGameInstance::Init() 
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UNetGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 4, FColor::Purple, TEXT("HOSTING"));


	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UNetGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 4, FColor::Purple, FString::Printf(TEXT("JOINING %s"), *Address));
}