// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"



bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	
	
	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	
	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitPressed);

	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(ConfirmJoinMenuButton != nullptr)) return false;
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}





void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr)) return;
		const FString Address = IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

 void UMainMenu::HostServer()
{
 
	 if (MenuInterface != nullptr)
	 {
		 MenuInterface->Host();
		 
	 }
 
}

 void UMainMenu::OpenJoinMenu()
 {
	 if (!ensure(MenuSwitcher != nullptr)) return;
	 if (!ensure(JoinMenu != nullptr)) return;
	 MenuSwitcher->SetActiveWidget(JoinMenu);
 }

 void UMainMenu::OpenMainMenu()
 {
	 if (!ensure(MenuSwitcher != nullptr)) return;
	 if (!ensure(MainMenu != nullptr)) return;
	 MenuSwitcher->SetActiveWidget(MainMenu);

 }

 void UMainMenu::ExitPressed() {

	 UWorld* World = GetWorld();
	 if (!ensure(World != nullptr)) return;

	 APlayerController* PlayerController = World->GetFirstPlayerController();
	 if (!ensure(PlayerController != nullptr)) return;

	 PlayerController->ConsoleCommand("quit");

 }