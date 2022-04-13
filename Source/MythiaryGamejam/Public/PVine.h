// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PGameData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "PVine.generated.h"

class APVineSegment;

UCLASS()
class MYTHIARYGAMEJAM_API APVine : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APVine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AttemptMoveInDirection(Direction MoveDirection);
	bool CanMoveInDirection(Direction MoveDirection);
	void MoveInDirection(Direction MoveDirection);
	void AddSegment(Direction MoveDirection);
	
	DECLARE_DELEGATE_OneParam(FMoveInDirection, Direction);

	/* Grid snapping length */
	UPROPERTY(EditAnywhere)
	float GridUnitLength = 100.f;

    /* Blueprint for ghost vine segments */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> VineSegmentGhostClass;

	/* Blueprint for straight vine segments */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> VineSegmentStraightClass;

	/* Blueprint for curved vine segments */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> VineSegmentCurveClass;

	FRotator GetStraightVineRotation(Direction MoveDirection);
	FRotator GetCurvedVineRotation(Direction MoveDirection);

	UPROPERTY()
	TArray<AActor*> VineParts;
	UPROPERTY()
	AActor* LastSegment = nullptr;
	
	Direction LastDirection = Direction::UP;
	UPROPERTY(EditAnywhere)
	FVector CurrentLocation = {50.f,50.f,50.f};

	UPROPERTY()
	class APGameModeBase* ActionSystem = nullptr;
	bool bPlayerHasAction = true;

	UFUNCTION()
	void PlayerTurn();
	UFUNCTION()
	void OtherTurn();

	UPROPERTY()
	APVineSegment* VineHead;

	UPROPERTY(EditAnywhere)
	bool bDrawDirectionArrows = true;

	UPROPERTY(EditAnywhere)
	int32 MaxActions = 5;

	UPROPERTY()
	int32 ActionsLeft;

	UFUNCTION()
	void MoveVine(bool bToEnd);
	
	UFUNCTION()
	void OnHurt();
	
	UFUNCTION()
	void PlantVine();
};
