#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOtherActorsAction);

UCLASS()
class MYTHIARYGAMEJAM_API APGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerAction OnPlayerAction;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOtherActorsAction OnOtherActorsAction;

	void PlayerUsedAction();
	void BroadcastPlayerAction();
	void BroadcastOtherActorsAction();

	UPROPERTY(EditAnywhere)
	float OtherActorsDelay = 1.0f;
	UPROPERTY(EditAnywhere)
	float PlayerDelay = 3.0f;

	void LoadLevel(const FName LevelName) const;
	void ReloadCurrentLevel() const;
	void NextLevel();

	int32 CheckCurrentLevelIndex();

	int32 CurrentLevel;
	
	UPROPERTY(EditAnywhere)
	TArray<FName> LevelNames;
};
