#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EndlesspeedGameModeBase.h"
#include "Coin.generated.h"

UCLASS()
class ENDLESSPEED_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Setup")
		UStaticMeshComponent* coinMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Setup")
		USphereComponent* collisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AEndlesspeedGameModeBase* myGamemode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
		void OnCoinBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
