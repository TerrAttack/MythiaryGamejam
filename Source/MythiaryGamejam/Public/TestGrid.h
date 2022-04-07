// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestCell.h"
#include "GameFramework/Actor.h"
#include "TestGrid.generated.h"

USTRUCT(BlueprintType)
struct FVectorInt
{
	GENERATED_BODY()

	//~ The following member variable will be accessible by Blueprint Graphs:
	// This is the tooltip for our test variable.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Test Variables")
	UPROPERTY(EditAnywhere)
	int32 X;
	
	UPROPERTY(EditAnywhere)
	int32 Y;

	UPROPERTY(EditAnywhere)
	int32 Z;

	//~ The following member variable will be not accessible by Blueprint Graphs:
	int32 NativeOnlyMemberVariable;

	/**~
	* This UObject pointer is not accessible to Blueprint Graphs, but
	* is visible to UE4's reflection, smart pointer, and garbage collection
	* systems.
	*/
	UPROPERTY()
	UObject* SafeObjectPointer;
};

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
	FVectorInt GridDimensions;

	UPROPERTY(EditAnywhere)
	FVectorInt CurrentPosition;
	
	UPROPERTY(EditAnywhere)
	FVectorInt TargetPosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestCell> VineCellClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestCell> EmptyCellClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestCell> CellClass;
	TArray<ATestCell*> Grid;

	ATestCell* GetCellByPosition(FVectorInt Position);

	UFUNCTION()
	void AttemptMoveInDirection(FVectorInt Direction);
};
