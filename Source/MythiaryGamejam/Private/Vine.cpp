// Fill out your copyright notice in the Description page of Project Settings.


#include "Vine.h"
#include "Engine/World.h"
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
    
    ///Set camera to orthographic
    /*
	auto Cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (Cam != nullptr)
	{
		Cam->bIsOrthographic = true;
		Cam->UnlockOrthoWidth();
		Cam->SetOrthoWidth(.01f);
	}
	*/
}

// Called every frame
void AVine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	// move down if going over an edge
	if (CanMoveInDirection(Direction::DOWN))
	{
		AddSegment(Direction::DOWN);
		MoveInDirection(Direction::DOWN);
	}
	// move normally if it is possible
	else if (CanMoveInDirection(MoveDirection))
	{
		AddSegment(MoveDirection);
		MoveInDirection(MoveDirection);
		//playeraction perform
	}
	else
	{
		// moves up if hitting a wall and has empty space above
		if (CanMoveInDirection(Direction::UP))
		{
			AddSegment(Direction::UP);
			MoveInDirection(Direction::UP);
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
		UClass* SpawnClass;
		FRotator Orientation = FRotator::ZeroRotator;

		SpawnClass = MoveDirection == LastDirection ? VineSegmentStraightClass : VineSegmentCurveClass;
		Orientation = MoveDirection == LastDirection ? GetStraightVineRotation(MoveDirection) : GetCurvedVineRotation(MoveDirection);

		/*
		if (MoveDirection == LastDirection)
		{
			SpawnClass = VineSegmentStraightClass;
			Orientation = GetStraightVineRotation(MoveDirection);
		}
		else
		{
			SpawnClass = VineSegmentCurveClass;
			Orientation = GetCurvedVineRotation(MoveDirection);
		}
		*/
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
	
	GetWorld()->LineTraceSingleByChannel(Hit, CurrentLocation, CurrentLocation + GridUnitLength * *MoveVector, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
	//GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() + GridUnitLength * *MoveVector, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
	return Hit.GetActor() == nullptr;
}

void AVine::MoveInDirection(Direction MoveDirection)
{
	FVector* MoveVector = Directions.Find(MoveDirection);
	if (MoveVector == nullptr)
	{
		return;
	}
	FVector TransformVector = GridUnitLength * *MoveVector;
	//SetActorLocation(GetActorLocation() + TransformVector);
	CurrentLocation += TransformVector;
}

