#include "PlayerPawn.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	playerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
	RootComponent = playerSphere;
	camera->SetupAttachment(RootComponent);

	// Setup Variables Constructor
	minSpeed = 1000.0f;
	maxSpeed = 4000.0f;
	forwardSpeed = minSpeed;
	bIsDead = false;
	mouseSensitivity = 1000.0f;
}


void APlayerPawn::MoveUp(float Value)
{
	movementInput.Y = Value;
}

void APlayerPawn::MoveRight(float Value)
{
	movementInput.X = Value;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsDead) {
		if (forwardSpeed < maxSpeed){
			forwardSpeed += 20.0f * DeltaTime;
		}
		AddMovementInput(GetActorUpVector(), mouseSensitivity * movementInput.Y);
		AddMovementInput(GetActorRightVector(), mouseSensitivity * movementInput.X);
		AddActorLocalOffset(ConsumeMovementInputVector() * DeltaTime, true);
		AddActorLocalOffset(FVector(1.0f, 0.0f, 0.0f) * forwardSpeed * DeltaTime, true);
		scoreSpeed = (forwardSpeed - minSpeed) / (maxSpeed - minSpeed);
	}
	if (bIsDead) {
		forwardSpeed = minSpeed;
	}

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APlayerPawn::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
}

