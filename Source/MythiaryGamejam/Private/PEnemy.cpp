
#include "PEnemy.h"

APEnemy::APEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APEnemy::Move()
{
	
}

void APEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void APEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

