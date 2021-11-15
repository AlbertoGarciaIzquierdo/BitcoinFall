#include "Coin.h"
#include "PlayerPawn.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Root component"));
	coinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh Component"));

	RootComponent = collisionSphere;
	coinMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	myGamemode = Cast<AEndlesspeedGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnCoinBeginOverlap);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	coinMesh->AddLocalRotation(FRotator(0.0f,90.0f * DeltaTime,0.0f));
}

void ACoin::OnCoinBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
	if (playerPawn)
	{
		if (myGamemode)
		{
			myGamemode->bCoinTaken = true;
			myGamemode->score += 10.0f;
		}
		Destroy();
	}
}

