// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PActionTest.generated.h"

UCLASS()
class MYTHIARYGAMEJAM_API APActionTest : public AActor
{
	GENERATED_BODY()
	
public:
	APActionTest();
	
	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void PlayerAction();
	UFUNCTION()
	void OtherAction();

	void PlayerDoesAction();

	bool bPlayerHasAction = true;
	
};
