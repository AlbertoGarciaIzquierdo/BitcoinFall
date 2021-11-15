#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Spawner.h"
#include "PlayerPawn.h"

class ASpawner;


#include "Tunnel.generated.h"


UCLASS()
class ENDLESSPEED_API ATunnel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATunnel();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh to Show")
		UStaticMeshComponent* TunnelMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh to Show")
		UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerZone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RotateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tunnel Spawner")
		ASpawner* TunnelSpawner;

	UFUNCTION()
		void RandomizeObstacle();

	UPROPERTY(BlueprintReadOnly)
		TArray<UStaticMesh*> ObstacleAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
