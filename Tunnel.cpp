#include "Tunnel.h"

// Sets default values
ATunnel::ATunnel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TunnelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tunnel Mesh"));
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	RootComponent = TunnelMesh;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->InitBoxExtent(FVector(32.0f, 500.0f, 500.0f));
	TriggerZone->SetWorldLocation(FVector(2532.0f, 0.0f, 0.0f));

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->SetWorldLocation(FVector(2500.0f, 0.0f, 0.0f));

	ObstacleMesh->SetupAttachment(RootComponent);
	ObstacleMesh->SetWorldLocation(FVector(2470.0f, 0.0f, 0.0f));

	/*if(!TunnelSpawner){
		TunnelSpawner = NULL;
	}*/

	RotateSpeed = 45.0f;


	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset0(TEXT("/Game/Tunnel/Obstacles/Obstacle01.Obstacle01"));
	ObstacleAsset.Add(ObstacleAsset0.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset1(TEXT("/Game/Tunnel/Obstacles/Obstacle02.Obstacle02"));
	ObstacleAsset.Add(ObstacleAsset1.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset2(TEXT("/Game/Tunnel/Obstacles/Obstacle03.Obstacle03"));
	ObstacleAsset.Add(ObstacleAsset2.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset3(TEXT("/Game/Tunnel/Obstacles/Obstacle04.Obstacle04"));
	ObstacleAsset.Add(ObstacleAsset3.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset4(TEXT("/Game/Tunnel/Obstacles/Obstacle05.Obstacle05"));
	ObstacleAsset.Add(ObstacleAsset4.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset5(TEXT("/Game/Tunnel/Obstacles/Obstacle06.Obstacle06"));
	ObstacleAsset.Add(ObstacleAsset5.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset6(TEXT("/Game/Tunnel/Obstacles/Obstacle07.Obstacle07"));
	ObstacleAsset.Add(ObstacleAsset6.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset7(TEXT("/Game/Tunnel/Obstacles/Obstacle08.Obstacle08"));
	ObstacleAsset.Add(ObstacleAsset7.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset8(TEXT("/Game/Tunnel/Obstacles/Obstacle09.Obstacle09"));
	ObstacleAsset.Add(ObstacleAsset8.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObstacleAsset9(TEXT("/Game/Tunnel/Obstacles/Obstacle10.Obstacle10"));
	ObstacleAsset.Add(ObstacleAsset9.Object);
}

void ATunnel::RandomizeObstacle()
{
	int32 randObstacle = FMath::RandRange(0,9);
	
	switch (randObstacle)
	{
	default:
		break;
	case 0:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[0]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 1:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[1]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 2:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[2]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 3:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[3]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 4:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[4]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 5:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[5]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 6:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[6]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 7:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[7]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 8:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[8]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	case 9:
		ObstacleMesh->SetStaticMesh(ObstacleAsset[9]);
		ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, FMath::RandRange(0, 360)));
		break;
	}
}

// Called when the game starts or when spawned
void ATunnel::BeginPlay()
{
	Super::BeginPlay();
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ATunnel::OnTriggerBeginOverlap);
	ObstacleMesh->OnComponentHit.AddDynamic(this, &ATunnel::OnWallHit);
}

// Called every frame
void ATunnel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ObstacleMesh->AddLocalRotation(FRotator(0.0f, 0.0f, RotateSpeed * DeltaTime));
}

void ATunnel::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerPawn>(OtherActor))
	{
		TunnelSpawner->SpawnTunnelatSpawnPoint();		
		Destroy();
	}

}

void ATunnel::OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Hello, me muero"));
	APlayerPawn* playerPawn = Cast<APlayerPawn>(OtherActor);
	
	if (playerPawn)
	{
		playerPawn->bIsDead = true;
	}
}

