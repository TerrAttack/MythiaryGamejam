// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGrid.h"

// Sets default values
ATestGrid::ATestGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	CurrentPosition = {0, 0, 0};
	TargetPosition = CurrentPosition;
}

// Called when the game starts or when spawned
void ATestGrid::BeginPlay()
{
	Super::BeginPlay();
	FRotator Rotation = FRotator::ZeroRotator;
	
	for (int32 Z = 0; Z < GridDimensions.Z; Z++)
	{
		for (int32 Y = 0; Y < GridDimensions.Y; Y++)
		{
			for (int32 X = 0; X < GridDimensions.X; X++)
			{
				//UE_LOG(LogTemp, Display, TEXT("%d, %d, %d"), X, Y, Z);
				FVector Location = FVector(X * 100.f, Y * 100.f, Z * 100.f);
				TSubclassOf<ATestCell> SpawnCell;
				int32 i = FMath::FRandRange(0, 20);

				switch (i)
				{
					default:
						SpawnCell = EmptyCellClass;
						break;
					case 1:
						SpawnCell = CellClass;
						break;
				}
				
				AActor* CellActor = GetWorld()->SpawnActor(SpawnCell);
				ATestCell* Cell = Cast<ATestCell>(CellActor);
				Grid.Add(Cell);

				CellActor->SetActorLocation(Location);
				CellActor->SetActorRotation(Rotation);
			}
		}
	}
}

// Called every frame
void ATestGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATestCell* ATestGrid::GetCellByPosition(FVector Position)
{
	int32 ArrayIndex = -1;
	
	if (IsInsideGrid(Position))
	{
		return  Grid[GridDimensions.X * GridDimensions.Y * Position.Z + GridDimensions.X * Position.Y + Position.X];
	}
	
	return nullptr;
}

void ATestGrid::AttemptMoveInDirection(FVector Direction)
{
	UE_LOG(LogTemp, Display, TEXT("ATTEMPTMOVE"));
	auto CurrentCel = GetCellByPosition(CurrentPosition);
	TargetPosition = CurrentPosition;
	TargetPosition.X += Direction.X;
	TargetPosition.Y += Direction.Y;
	TargetPosition.Z += Direction.Z;
	
	ATestCell* TargetCel = GetCellByPosition(TargetPosition);
	
	if (TargetCel == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("MoveFail!"));
	}
	
	else
	{
		UE_LOG(LogTemp, Display, TEXT("MoveSucces!"));
		CurrentPosition = TargetPosition;

		const int32 IndexOfCell = GridDimensions.X * GridDimensions.Y * CurrentPosition.Z + GridDimensions.X * CurrentPosition.Y + CurrentPosition.X;
		Grid.RemoveAt(IndexOfCell);
		TargetCel->Destroy();
		
		AActor* NewCellActor = GetWorld()->SpawnActor(VineCellClass);
		const FVector Location = FVector(CurrentPosition.X * 100.f, CurrentPosition.Y * 100.f, CurrentPosition.Z * 100.f);
		const FRotator Rotation = FRotator::ZeroRotator;
		NewCellActor->SetActorLocation(Location);
		NewCellActor->SetActorRotation(Rotation);
		ATestCell* NewCell = Cast<ATestCell>(NewCellActor);
		Grid.Insert(NewCell, IndexOfCell);
	}
}

bool ATestGrid::IsInsideGrid(FVector Position)
{
	if (Grid.IsEmpty()) return false;
	return Position.X >= 0 && Position.X < GridDimensions.X &&
			Position.Y >= 0 && Position.Y < GridDimensions.Y &&
			Position.Z >= 0 && Position.Z < GridDimensions.Z;
}

