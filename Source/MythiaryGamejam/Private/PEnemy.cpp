
#include "PEnemy.h"

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
	Timer(WayPoints);
}

void APEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp,Warning,TEXT("Array length: %i"),WayPoints.Num());
}

void APEnemy::Timer(const TArray<AActor*> WayPointArray)
{
	const FTimerDelegate MoveDelegate = FTimerDelegate::CreateUObject(this,&APEnemy::Move, WayPointArray);
	GetWorldTimerManager().SetTimer(TimerHandle, MoveDelegate,2, false);
}

void APEnemy::ReverseArray()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),WayPointClass,WayPoints);
	int n = 3;
	AActor* Temp;
	for (int i = 0; i < n / 2; i++)
	{
		Temp = WayPoints[i];
		WayPoints[i] = WayPoints[n - i -1];
		WayPoints[n-i-1] = Temp;
	}
	Timer(WayPoints);
	
}

void APEnemy::Move(TArray<AActor*>WayPointArray)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	for (AActor* WayPoint : WayPointArray)
	{
		TeleportTo(WayPoint->GetActorLocation(),WayPoint->GetActorRotation(),false,false);
	}
	WayPoints.Pop();
	if(WayPoints.Num() > 0)  Timer(WayPoints);
		else ReverseArray();
}

void APEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning, TEXT("yes"));
}



