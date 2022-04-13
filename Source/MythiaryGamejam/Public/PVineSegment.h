// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PVineSegment.generated.h"

class APVine;

UCLASS()
class MYTHIARYGAMEJAM_API APVineSegment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APVineSegment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	APVine* Vine = nullptr;

	UFUNCTION()
	void OnHurt();
};
