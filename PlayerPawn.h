#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class ENDLESSPEED_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCameraComponent* camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* playerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Variables")
		float scoreSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup Variables")
		float forwardSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup Variables")
		float maxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup Variables")
		float minSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D movementInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mouseSensitivity;

	UFUNCTION()
		void MoveUp(float Value);
	UFUNCTION()
		void MoveRight(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
