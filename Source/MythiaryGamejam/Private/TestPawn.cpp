// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"

#include "GameData.h"
//#include "TestGrid.h"
#include "GameData.h"
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
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveBack"), IE_Pressed, this, &ATestPawn::MoveInDirection, Direction::BACK);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveForward"), IE_Pressed, this, &ATestPawn::MoveInDirection, Direction::FORWARD);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveLeft"), IE_Pressed, this, &ATestPawn::MoveInDirection, Direction::LEFT);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveRight"), IE_Pressed, this, &ATestPawn::MoveInDirection, Direction::RIGHT);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveDown"), IE_Pressed, this, &ATestPawn::MoveInDirection, Direction::DOWN);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveUp"), IE_Pressed, this, &ATestPawn::MoveInDirection, Direction::UP);
}

void ATestPawn::MoveInDirection(Direction MoveDirection)
{
	if (Grid != nullptr)
	{
		FVector* Val = Directions.Find(MoveDirection);
		if (Val != nullptr) Grid->AttemptMoveInDirection(*Val);
	}
}

