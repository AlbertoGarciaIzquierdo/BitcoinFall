#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Spawner.generated.h"

UCLASS()
class ENDLESSPEED_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UFUNCTION(BlueprintCallable)
		void SpawnTunnel(FVector spawnLocation);
	UFUNCTION(BlueprintCallable)
		void SpawnCoin(FVector spawnLocation);
	UFUNCTION(BlueprintCallable)
		void SpawnTunnelatSpawnPoint();
	UFUNCTION(BlueprintCallable)
		void SpawnInitialTunnels();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor to Spawn")
		TSubclassOf<class ATunnel> actorToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin to Spawn")
		TSubclassOf<class ACoin> coinToSpawn;

	UPROPERTY(BlueprintReadOnly)
		class ATunnel* NewestTunnel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
