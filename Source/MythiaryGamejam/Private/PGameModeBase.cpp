#include "PGameModeBase.h"

void APGameModeBase::StartPlay()
{
	Super::StartPlay();
	OnPlayerAction.Broadcast();
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
