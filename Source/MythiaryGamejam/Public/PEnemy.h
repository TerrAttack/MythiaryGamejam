
#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PEnemy.generated.h"

UCLASS()
class MYTHIARYGAMEJAM_API APEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	APEnemy();
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* HitBox;
	UPROPERTY(EditAnywhere)
	FVector NewLocation;
public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> WayPoints;
	virtual void Tick(float DeltaTime) override;
	void Move(TArray<AActor*> WayPoints);
	void Timer(TArray<AActor*>WayPoints);
	void ReverseArray();
	void OtherAction();
	bool bMoveBack;
	int32 Index;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WayPointClass;
private:
	FTimerHandle TimerHandle;
};
