#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGame/Controllers/BeaverPlayerController.h"
#include "Components/SceneComponent.h"
#include "../SpawObject.h"
#include "Resource.generated.h"

struct FResourceProperties;


UENUM(BlueprintType)
enum ResourceType //The types of resources
{
	Roots UMETA(DisplayName = "Roots"),
	Logs UMETA(DisplayName = "Logs"),
	Stone UMETA(DisplayName = "Stone"),
	Berry UMETA(DisplayName = "Berry")
};

UCLASS()
class BEAVERGAME_API AResource : public AActor
{
	GENERATED_BODY()
	
public:	

	AResource();

	UPROPERTY(EditAnywhere)
	USceneComponent* ResourceScene;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ResourceMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision; //The collider for detecting the player

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditAnywhere, Category = Resource)
	TEnumAsByte<ResourceType> Type; //The type of resource, berry, stone, logs etc

	UPROPERTY(EditAnywhere, Category = Resource) 
	int resourceAmount; //The amount of the resource to give to the player on pickup

};
