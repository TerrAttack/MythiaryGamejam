
#include "PEnemy.h"

APEnemy::APEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

