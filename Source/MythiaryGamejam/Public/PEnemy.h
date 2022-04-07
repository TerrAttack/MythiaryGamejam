
#pragma once

#include "CoreMinimal.h"
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

public:	
	virtual void Tick(float DeltaTime) override;
};
