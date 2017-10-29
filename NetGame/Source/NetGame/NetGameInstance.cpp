// Fill out your copyright notice in the Description page of Project Settings.

#include "NetGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"

#include "MenuSystem/MainMenu.h"



UNetGameInstance::UNetGameInstance(const FObjectInitializer & ObjectInitializer) 
{
	//FClassFinder
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	
	MenuClass = MenuBPClass.Class;
	

}

void UNetGameInstance::Init() 
{
	
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
	
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

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UNetGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	
	if (!ensure(Menu != nullptr)) return;

	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;

	Menu->SetMenuInterface(this);
}