#include "PGameModeBase.h"

#include "Kismet/GameplayStatics.h"

void APGameModeBase::StartPlay()
{
	Super::StartPlay();
	OnPlayerAction.Broadcast();
	CurrentLevel = 0;
}

void APGameModeBase::PlayerUsedAction()
{
	FTimerHandle OtherActorsActionBroadcastDelay_TimerHandle;
	GetWorldTimerManager().SetTimer(OtherActorsActionBroadcastDelay_TimerHandle, this, &APGameModeBase::BroadcastOtherActorsAction, OtherActorsDelay);
}

void APGameModeBase::BroadcastPlayerAction()
{
	OnPlayerAction.Broadcast();
}

void APGameModeBase::BroadcastOtherActorsAction()
{
	OnOtherActorsAction.Broadcast();
	
	FTimerHandle PlayerActionBroadcastDelay_TimerHandle;
	GetWorldTimerManager().SetTimer(PlayerActionBroadcastDelay_TimerHandle, this, &APGameModeBase::BroadcastPlayerAction, PlayerDelay);
}

void APGameModeBase::LoadLevel(const FName LevelName) const
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName, false);
}

void APGameModeBase::ReloadCurrentLevel() const
{
	UGameplayStatics::OpenLevel(GetWorld(),FName(*GetWorld()->GetName()), false);
}

void APGameModeBase::NextLevel()
{
	CurrentLevel = CheckCurrentLevelIndex() + 1;
	if(CurrentLevel < LevelNames.Num())
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelNames[CurrentLevel], false);
	}
}

int32 APGameModeBase::CheckCurrentLevelIndex()
{
	for (int32 i = 0; i < LevelNames.Num(); i++)
	{
		if(LevelNames[i] == FName(*GetWorld()->GetName()))
		{
			return i;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Current level not indexed in PGameModeBase"));
	return 0;
}

