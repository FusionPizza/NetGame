// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NETGAME_API UNetGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
		UNetGameInstance(const FObjectInitializer & ObjectInitializer);
	
		virtual void Init();

		UFUNCTION(BluePrintCallable)
		void LoadMenu();

		UFUNCTION(BluePrintCallable)
		void InGameLoadMenu();
		UFUNCTION(Exec)
		void Host();

		UFUNCTION(Exec)
		void Join(const FString& Address);

		virtual void LoadMainMenu() override;

private:
	TSubclassOf<class UUserWidget > MenuClass;
	TSubclassOf<class UUserWidget > InGameMenuClass;

	class UMainMenu* Menu;

};
