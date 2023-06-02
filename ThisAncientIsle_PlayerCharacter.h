#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AncientIsle/Interactive/NoteObject.h"
#include "AncientIsle/Interactive/RunePuzzle.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundCue.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class ANCIENTISLE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDisablePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additional Components")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additional Components")
	UStaticMeshComponent* CarryItemMesh;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	float CameraRotationSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carry Items")
	float TraceDistance = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carry Items")
	AActor* ItemActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Carry Items")
	int TalismanCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note Properties")
	FString NoteAddresse = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note Properties")
	FString NoteMain = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note Properties")
	FString NoteSender = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note Properties")
	ANoteObject* NoteObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
	USoundCue* TalismanSfx = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DropItem();

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayNote(); //Blueprint Event

private:

	void MoveForward(float axis);

	void MoveRight(float axis);

	void LookUp(float axis);

	void LookRight(float axis);

	void PlayerJump();

	void PickupItem();

};
