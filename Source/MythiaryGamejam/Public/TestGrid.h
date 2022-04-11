// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestCell.h"
#include "GameData.h"
#include "GameFramework/Actor.h"
#include "TestGrid.generated.h"

UCLASS()
class MYTHIARYGAMEJAM_API ATestGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector GridDimensions;

	UPROPERTY(EditAnywhere)
	FVector CurrentPosition;
	
	UPROPERTY(EditAnywhere)
	FVector TargetPosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestCell> VineCellClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestCell> EmptyCellClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestCell> CellClass;
	TArray<ATestCell*> Grid;

	ATestCell* GetCellByPosition(FVector Position);

	UFUNCTION()
	void AttemptMoveInDirection(FVector Direction);

	UFUNCTION()
	bool IsInsideGrid(FVector Position);
};
