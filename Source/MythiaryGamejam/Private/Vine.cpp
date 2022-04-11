// Fill out your copyright notice in the Description page of Project Settings.


#include "Vine.h"

#include "PActionTest.h"
#include "PGameModeBase.h"
#include "Engine/World.h"
#include "UObject/Class.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVine::AVine()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AVine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVine::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ActionSystem = GetWorld()->GetAuthGameMode<APGameModeBase>();
	if (ActionSystem == nullptr) return;
	ActionSystem->OnPlayerAction.AddDynamic(this, &AVine::PlayerTurn);
	ActionSystem->OnOtherActorsAction.AddDynamic(this, &AVine::OtherTurn);
	ActionSystem->PlayerDelay = .1f;
	ActionSystem->OtherActorsDelay = .1f;
}

// Called to bind functionality to input
void AVine::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveBack"), IE_Pressed, this, &AVine::AttemptMoveInDirection, Direction::BACK);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveForward"), IE_Pressed, this, &AVine::AttemptMoveInDirection, Direction::FORWARD);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveLeft"), IE_Pressed, this, &AVine::AttemptMoveInDirection, Direction::LEFT);
	PlayerInputComponent->BindAction<FMoveInDirection>(TEXT("MoveRight"), IE_Pressed, this, &AVine::AttemptMoveInDirection, Direction::RIGHT);
}

void AVine::AttemptMoveInDirection(Direction MoveDirection)
{
	if (ActionSystem == nullptr || !bPlayerHasAction) return;

	// move down if going over an edge
	if (CanMoveInDirection(Direction::DOWN))
	{
		MoveInDirection(Direction::DOWN);
		ActionSystem->PlayerUsedAction();
	}
	
	// move normally if it is possible
	else if (CanMoveInDirection(MoveDirection))
	{
		MoveInDirection(MoveDirection);
		ActionSystem->PlayerUsedAction();
	}
	else
	{
		// moves up if hitting a wall and has empty space above
		if (CanMoveInDirection(Direction::UP))
		{
			MoveInDirection(Direction::UP);
			ActionSystem->PlayerUsedAction();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("CANNOTMOVE"));
		}
	}
}

void AVine::AddSegment(Direction MoveDirection)
{
	if (VineSegmentStraightClass != nullptr && VineSegmentCurveClass != nullptr)
	{
		const FRotator Orientation = MoveDirection == LastDirection ? GetStraightVineRotation(MoveDirection) : GetCurvedVineRotation(MoveDirection);
		UClass* SpawnClass = MoveDirection == LastDirection ? VineSegmentStraightClass : VineSegmentCurveClass;
		AActor* VineSegment = GetWorld()->SpawnActor<AActor>(SpawnClass, CurrentLocation, Orientation);
		LastSegment = VineSegment;
		LastDirection = MoveDirection;
		VineParts.Add(VineSegment);
	}
}

FRotator AVine::GetStraightVineRotation(Direction MoveDirection)
{
	FRotator Orientation = FRotator::ZeroRotator;
	
	if (MoveDirection == Direction::LEFT || MoveDirection == Direction::RIGHT)
	{
		Orientation = {0,90, 0};
	}
	else if (MoveDirection == Direction::UP || MoveDirection == Direction::DOWN)
	{
		Orientation = {90,0,0};
	}

	return Orientation;
}

FRotator AVine::GetCurvedVineRotation(Direction MoveDirection)
{
	FRotator Orientation = FRotator::ZeroRotator;

	// __
	//  I 
	if (LastDirection == Direction::FORWARD && MoveDirection == Direction::LEFT ||
		LastDirection == Direction::RIGHT && MoveDirection == Direction::BACK)
	{
		Orientation = {0,180,0};
	}
	
	//   I
	// __I
	else if (LastDirection == Direction::BACK && MoveDirection == Direction::LEFT ||
		LastDirection == Direction::RIGHT && MoveDirection == Direction::FORWARD)
	{
		Orientation = {0,-90,0};
	}
	// I
	// I__
	// Not necessary, this is the default orientation
	else if (LastDirection == Direction::BACK && MoveDirection == Direction::RIGHT ||
		LastDirection == Direction::LEFT && MoveDirection == Direction::FORWARD)
	{
		Orientation = FRotator::ZeroRotator;
	}

	//  __
	// I 
	else if (LastDirection == Direction::FORWARD && MoveDirection == Direction::RIGHT ||
	LastDirection == Direction::LEFT && MoveDirection == Direction::BACK)
	{
		Orientation = {0,90,0};
	}
	
	////////////////////

	else if (LastDirection == Direction::FORWARD && MoveDirection == Direction::UP ||
	LastDirection == Direction::DOWN && MoveDirection == Direction::BACK)
	{
		Orientation = {90,90,0};
	}
	
	else if (LastDirection == Direction::LEFT && MoveDirection == Direction::UP ||
	LastDirection == Direction::DOWN && MoveDirection == Direction::RIGHT)
	{
		Orientation = {90,0,0};
	}

	else if (LastDirection == Direction::BACK && MoveDirection == Direction::UP ||
	LastDirection == Direction::DOWN && MoveDirection == Direction::FORWARD)
	{
		Orientation = {90,270,0};
	}
	
	else if (LastDirection == Direction::RIGHT && MoveDirection == Direction::UP ||
	LastDirection == Direction::DOWN && MoveDirection == Direction::LEFT)
	{
		Orientation = {90,180,0};
	}

	//////////////////////

	//WIP
	/*
	else if (LastDirection == Direction::UP)
	{
		if (MoveDirection == Direction::RIGHT) Orientation = {-90,0,0};
		else if (MoveDirection == Direction::BACK) Orientation = {-90,90,0};
		else if (MoveDirection == Direction::)
	}*/
	
	else if (LastDirection == Direction::UP && MoveDirection == Direction::RIGHT ||
	LastDirection == Direction::LEFT && MoveDirection == Direction::DOWN)
	{
		Orientation = {-90,0,0};
	}

	else if (LastDirection == Direction::UP && MoveDirection == Direction::BACK ||
	LastDirection == Direction::FORWARD && MoveDirection == Direction::DOWN)
	{
		Orientation = {-90,90,0};
	}

	else if (LastDirection == Direction::UP && MoveDirection == Direction::LEFT ||
	LastDirection == Direction::RIGHT && MoveDirection == Direction::DOWN)
	{
		Orientation = {-90,180,0};
	}

	else if (LastDirection == Direction::UP && MoveDirection == Direction::FORWARD ||
	LastDirection == Direction::BACK && MoveDirection == Direction::DOWN)
	{
		Orientation = {-90,270,0};
	}
	
	return Orientation;
}

void AVine::PlayerTurn()
{
	bPlayerHasAction = true;
	UE_LOG(LogTemp, Display, TEXT("Player gets turn"));
}

void AVine::OtherTurn()
{
	bPlayerHasAction = false;
	UE_LOG(LogTemp, Display, TEXT("Other gets turn"));
}


bool AVine::CanMoveInDirection(Direction MoveDirection)
{
	FHitResult Hit;
	FVector* MoveVector = Directions.Find(MoveDirection);
	if (MoveVector == nullptr)
	{
		return false;
	}

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(Hit,
		CurrentLocation,
		CurrentLocation + GridUnitLength * *MoveVector,
		ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
	
	return Hit.GetActor() == nullptr;
}

void AVine::MoveInDirection(Direction MoveDirection)
{
	AddSegment(MoveDirection);
	const FVector* MoveVector = Directions.Find(MoveDirection);
	if (MoveVector == nullptr) return;
	const FVector TransformVector = GridUnitLength * *MoveVector;
	CurrentLocation += TransformVector;
	bPlayerHasAction = false;
}

