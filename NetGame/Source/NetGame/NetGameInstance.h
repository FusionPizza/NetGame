// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NETGAME_API UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
		UNetGameInstance(const FObjectInitializer & ObjectInitializer);
	
		virtual void Init();

		UFUNCTION(Exec)
			void Host();

		UFUNCTION(Exec)
			void Join(const FString& Address);
};
