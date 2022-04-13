
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
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	FVector NewLocation;
public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> WayPoints;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void Move();
	bool bMoveBack;
	int32 Index;
	void Timer();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WayPointClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* HitBox;
private:
	FTimerHandle TimerHandle;
};
