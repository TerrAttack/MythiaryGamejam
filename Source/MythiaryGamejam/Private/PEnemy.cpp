
#include "PEnemy.h"

#include "GameModeInfoCustomizer.h"
#include "PActionTest.h"
#include "PGameModeBase.h"
#include "Kismet/GameplayStatics.h"

APEnemy::APEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	HitBox = CreateDefaultSubobject<USphereComponent>("HitBox");
	HitBox->SetupAttachment(BaseMesh);
}

void APEnemy::BeginPlay()
{
	Super::BeginPlay();
	Timer();
}

void APEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(APGameModeBase* GameMode = GetWorld()->GetAuthGameMode<APGameModeBase>())
	{
		GameMode->OnOtherActorsAction.AddDynamic(this, &APEnemy::OtherAction);
	}
}

void APEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APEnemy::OtherAction()
{
	if(!bMoveBack && Index > WayPoints.Num()-2) bMoveBack = true;
	if(bMoveBack && Index <= 1) bMoveBack = false;
	if(bMoveBack) Index--;
	if(!bMoveBack) Index++;
	TeleportTo(WayPoints[Index]->GetActorLocation(),WayPoints[Index]->GetActorRotation(),false,false );
	Timer();
}

void APEnemy::Timer()
{
	GetWorldTimerManager().SetTimer(TimerHandle,this, &APEnemy::OtherAction,2, false);
}

void APEnemy::ReverseArray()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),WayPointClass,WayPoints);
	int n = WayPoints.Num();
	AActor* Temp;
	for (int i = 0; i < n / 2; i++)
	{
		Temp = WayPoints[i];
		WayPoints[i] = WayPoints[n - i -1];
		WayPoints[n-i-1] = Temp;
	}
	Timer();
}


void APEnemy::Move(TArray<AActor*>WayPointArray)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	for (AActor* WayPoint : WayPointArray)
	{
		TeleportTo(WayPoint->GetActorLocation(),WayPoint->GetActorRotation(),false,false);
	}
	WayPoints.Pop();
	if(WayPoints.Num() > 0)  Timer();
		else ReverseArray();
}

void APEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning, TEXT("yes"));
}



