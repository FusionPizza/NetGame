// Fill out your copyright notice in the Description page of Project Settings.

#include "NetGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"




UNetGameInstance::UNetGameInstance(const FObjectInitializer & ObjectInitializer) 
{
	//FClassFinder
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	
	MenuClass = MenuBPClass.Class;

	//FClassFinder
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	InGameMenuClass = InGameMenuBPClass.Class;
	

}

void UNetGameInstance::Init() 
{
	
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
	
}

void UNetGameInstance::Host()
{
	if (Menu != nullptr) {
		Menu->Teardown();
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 4, FColor::Purple, TEXT("HOSTING"));


	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UNetGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr) {
		Menu->Teardown();
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 4, FColor::Purple, FString::Printf(TEXT("JOINING %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UNetGameInstance::LoadMainMenu()
{

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);

}

void UNetGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	
	if (!ensure(Menu != nullptr)) return;


	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UNetGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	if (!ensure(Menu != nullptr)) return;


	Menu->Setup();
	Menu->SetMenuInterface(this);
}