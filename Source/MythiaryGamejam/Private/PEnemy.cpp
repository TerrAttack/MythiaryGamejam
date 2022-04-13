
#include "PEnemy.h"

#include "GameModeInfoCustomizer.h"
#include "PActionTest.h"
#include "PGameModeBase.h"
#include "PVine.h"

#include "PVineSegment.h"

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
	//Timer();
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &APEnemy::OnBeginOverlap);
}

void APEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(APGameModeBase* GameMode = GetWorld()->GetAuthGameMode<APGameModeBase>())
	{
		GameMode->OnOtherActorsAction.AddDynamic(this, &APEnemy::Move);
	}
}

void APEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APEnemy::Move()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),JumpSound,GetActorLocation(),GetActorRotation());
	UE_LOG(LogTemp,Warning,TEXT("haha yeah"));
	if(!bMoveBack && Index > WayPoints.Num()-2) bMoveBack = true;
	if(bMoveBack && Index <= 1) bMoveBack = false;
	if(bMoveBack) Index--;
	if(!bMoveBack) Index++;
	SetActorLocationAndRotation(WayPoints[Index]->GetActorLocation(),WayPoints[Index]->GetActorRotation());
	//Timer();
}

void APEnemy::Timer()
{
	GetWorldTimerManager().SetTimer(TimerHandle,this, &APEnemy::Move,2, false);
}

void APEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("yes"));
	if(Cast<APVine>(OtherActor))
	UE_LOG(LogTemp,Warning,TEXT("outside of if"));
	APVineSegment* Vine = Cast<APVineSegment>(OtherActor);
	if(Vine)
	{
		Vine->OnHurt(); 
	}
}



