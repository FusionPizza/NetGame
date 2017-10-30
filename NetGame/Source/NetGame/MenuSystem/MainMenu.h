// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenu.generated.h"


/**
 * 
 */
UCLASS()
class NETGAME_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:




protected:
	virtual bool Initialize();
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;
	
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton*  CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton*  ConfirmJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField;



	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();


	
};
