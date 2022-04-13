// Fill out your copyright notice in the Description page of Project Settings.


#include "PVineSegment.h"

#include "PVine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APVineSegment::APVineSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APVineSegment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APVineSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APVineSegment::OnHurt()
{
	auto FlutVine = Cast<APVine>(UGameplayStatics::GetActorOfClass(GetWorld(), APVine::StaticClass())) ;
	if (FlutVine != nullptr)
	{
		FlutVine->OnHurt();
	}
}

void APVineSegment::PlantVine()
{
	auto FlutVine = Cast<APVine>(UGameplayStatics::GetActorOfClass(GetWorld(), APVine::StaticClass())) ;
	if (FlutVine != nullptr)
	{
		FlutVine->PlantVine();
	}
}

