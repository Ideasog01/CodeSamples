#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "BeaverGame/Controllers/BeaverPlayerController.h"

#include "BuildObject.generated.h"

UCLASS()
class BEAVERGAME_API ABuildObject : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ObjectMesh;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereCollision; //The collider for detecting the player. Collision = Display object resource requirements.
	
public:	
	// Sets default values for this actor's properties
	ABuildObject();

	void Build();

private:

	//THe required resources

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
	int requiredRoots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
	int requiredLogs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
	int requiredStone = 0;

	//The name of the object to display when the player is near

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
	FString buildObjectName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	ABeaverPlayerController* BeaverController;

};
