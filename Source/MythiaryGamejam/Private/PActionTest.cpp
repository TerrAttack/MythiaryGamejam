#include "PActionTest.h"

#include "PGameModeBase.h"


APActionTest::APActionTest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APActionTest::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(APGameModeBase* GameMode = GetWorld()->GetAuthGameMode<APGameModeBase>())
	{
		GameMode->OnPlayerAction.AddDynamic(this, &APActionTest::PlayerAction);
		GameMode->OnOtherActorsAction.AddDynamic(this, &APActionTest::OtherAction);
	}
}

void APActionTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bPlayerHasAction)
	{
		bPlayerHasAction = false;
		FTimerHandle PlayerDoesActionDelay_TimerHandle;
		GetWorldTimerManager().SetTimer(PlayerDoesActionDelay_TimerHandle, this, &APActionTest::PlayerDoesAction, 1.0f);
	}
}

void APActionTest::PlayerAction()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerActionTurn"));
	bPlayerHasAction = true;
}

void APActionTest::OtherAction()
{
	UE_LOG(LogTemp, Warning, TEXT("OtherActionTurn"));
}

void APActionTest::PlayerDoesAction()
{
	if(APGameModeBase* GameMode = GetWorld()->GetAuthGameMode<APGameModeBase>())
	{
		GameMode->PlayerUsedAction();
	}
}


