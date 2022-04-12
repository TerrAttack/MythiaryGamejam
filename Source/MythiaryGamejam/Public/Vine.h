// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "GameFramework/Pawn.h"
#include "Vine.generated.h"

UCLASS()
class MYTHIARYGAMEJAM_API AVine : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AttemptMoveInDirection(Direction MoveDirection);
	bool CanMoveInDirection(Direction MoveDirection);
	void MoveInDirection(Direction MoveDirection);
	void AddSegment(Direction MoveDirection);
	
	DECLARE_DELEGATE_OneParam(FMoveInDirection, Direction);

	UPROPERTY(EditAnywhere)
	float GridUnitLength = 100.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> VineSegmentStraightClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> VineSegmentCurveClass;

	FRotator GetStraightVineRotation(Direction MoveDirection);
	FRotator GetCurvedVineRotation(Direction MoveDirection);
	
	TArray<AActor*> VineParts;
	AActor* LastSegment = nullptr;
	Direction LastDirection = Direction::FORWARD;

	//FVector LastLocation;
	FVector CurrentLocation = {50.f,50.f,50.f};
};
