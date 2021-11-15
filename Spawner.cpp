#include "Spawner.h"
#include "Tunnel.h"
#include "Coin.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawner::SpawnTunnel(FVector spawnLocation)
{
	NewestTunnel = GetWorld()->SpawnActor<ATunnel>(actorToSpawn, spawnLocation, FRotator(0.0f,0.0f,0.0f));
	NewestTunnel->TunnelSpawner = this;
	NewestTunnel->RandomizeObstacle();
}

void ASpawner::SpawnCoin(FVector spawnLocation)
{
	GetWorld()->SpawnActor<ACoin>(coinToSpawn, spawnLocation, FRotator(0.0f, 0.0f, 0.0f));
}

void ASpawner::SpawnTunnelatSpawnPoint()
{
	SpawnTunnel(NewestTunnel->SpawnPoint->GetComponentLocation());
	SpawnCoin(NewestTunnel->SpawnPoint->GetComponentLocation() + FVector(1000.0f, FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-200.0f, 200.0f)));
}

void ASpawner::SpawnInitialTunnels()
{
	for (TActorIterator<ATunnel> OldTunnels(GetWorld()); OldTunnels; ++OldTunnels)
	{
		OldTunnels->Destroy();
	}
	for (TActorIterator<ACoin> OldCoins(GetWorld()); OldCoins; ++OldCoins)
	{
		OldCoins->Destroy();
	}
	for (int i = 0; i < 3; i++) {
		if (!IsValid(NewestTunnel)) {
			SpawnTunnel(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
		}
		if (IsValid(NewestTunnel)) {
			SpawnTunnelatSpawnPoint();
		}
	}
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnInitialTunnels();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

