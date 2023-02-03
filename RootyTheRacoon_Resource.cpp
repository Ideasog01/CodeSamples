#include "BeaverGame/Interaction/Resource.h"

AResource::AResource()
{

	ResourceScene = CreateDefaultSubobject<USceneComponent>(TEXT("Resource Scene Component"));
	SetRootComponent(ResourceScene);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SphereCollision->SetupAttachment(RootComponent);

	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Resource Mesh"));
	ResourceMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ResourceMesh->SetupAttachment(RootComponent);
}


void AResource::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AResource::OnOverlapBegin);
	PlayerController = Cast<ABeaverPlayerController>(GetWorld()->GetFirstPlayerController()); //Gets the player controller for adding resource
}

void AResource::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player")) //If the player is near, hide the resource and add the values to the player controller
	{
		//Add Resource to Inventory
		
		if(PlayerController != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Resource Added!"));
			PlayerController->AddResource(Type, resourceAmount);
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			SetActorTickEnabled(false);
		}
	}
}
