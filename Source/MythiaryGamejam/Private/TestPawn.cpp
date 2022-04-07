// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"

#include "TestGrid.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATestPawn::ATestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATestGrid::StaticClass());
	Grid = Cast<ATestGrid>(FoundActor);
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("MoveForward"), IE_Pressed, this, &ATestPawn::MoveForward);
	PlayerInputComponent->BindAction(TEXT("MoveBack"), IE_Pressed, this, &ATestPawn::MoveBack);
	PlayerInputComponent->BindAction(TEXT("MoveRight"), IE_Pressed, this, &ATestPawn::MoveRight);
	PlayerInputComponent->BindAction(TEXT("MoveLeft"), IE_Pressed, this, &ATestPawn::MoveLeft);
	PlayerInputComponent->BindAction(TEXT("MoveUp"), IE_Pressed, this, &ATestPawn::MoveUp);
	PlayerInputComponent->BindAction(TEXT("MoveDown"), IE_Pressed, this, &ATestPawn::MoveDown);
}

void ATestPawn::MoveForward()
{
	UE_LOG(LogTemp, Display, TEXT("FORWARD"));
	if (Grid != nullptr)
	{
		Grid->AttemptMoveInDirection({1,0,0});
	}
}

void ATestPawn::MoveBack()
{
	UE_LOG(LogTemp, Display, TEXT("BACK"));
	if (Grid != nullptr)
	{
		Grid->AttemptMoveInDirection({-1,0,0});
	}
}

void ATestPawn::MoveRight()
{
	UE_LOG(LogTemp, Display, TEXT("RIGHT"));
	if (Grid != nullptr)
	{
		Grid->AttemptMoveInDirection({0,1,0});
	}
}

void ATestPawn::MoveLeft()
{
	UE_LOG(LogTemp, Display, TEXT("LEFT"));
	if (Grid != nullptr)
	{
		Grid->AttemptMoveInDirection({0,-1,0});
	}
}

void ATestPawn::MoveUp()
{
	UE_LOG(LogTemp, Display, TEXT("LEFT"));
	if (Grid != nullptr)
	{
		Grid->AttemptMoveInDirection({0,0,1});
	}
}

void ATestPawn::MoveDown()
{
	UE_LOG(LogTemp, Display, TEXT("LEFT"));
	if (Grid != nullptr)
	{
		Grid->AttemptMoveInDirection({0,0,-1});
	}
}


