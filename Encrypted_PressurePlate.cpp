#include "Encrypted/Interactive/PressurePlate.h"
#include "Encrypted/Interactive/Door.h"
#include "Encrypted/Interactive/LaserBeam.h"

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	InteractiveCollider->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	InteractiveCollider->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}


void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("Player")) //If the actor is not valid, abort
	{
		return;
	}

	//Activate all assigned objects

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Pressure Plate Active");

	for (int i = 0; i < AttachedDoorArray.Num(); i++)
	{
		if (AttachedDoorArray[i])
		{
			AttachedDoorArray[i]->OpenDoor(true);
		}
	}

	for (int l = 0; l < AttachedLaserBeamArray.Num(); l++)
	{
		if (AttachedLaserBeamArray[l])
		{
			AttachedLaserBeamArray[l]->ToggleBeamActivation(false);
		}
	}
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Check if any actors are still on the pressure plate

	TArray<AActor*> OverlappingActors;
	InteractiveCollider->GetOverlappingActors(OverlappingActors, TSubclassOf<AActor>());

	for (int i = 0; i < OverlappingActors.Num(); i++) //Check all actors on the pressure plate are valid
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, OverlappingActors[i]->GetName());

		if (OverlappingActors[i]->ActorHasTag("Player"))
		{
			return; //If valid actor is still on pressure plate, abort
		}
	}

	//Deactivate all assigned objects

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Pressure Plate Disabled");

	for (int i = 0; i < AttachedDoorArray.Num(); i++)
	{
		if (AttachedDoorArray[i])
		{
			AttachedDoorArray[i]->OpenDoor(false);
		}
	}

	for (int l = 0; l < AttachedLaserBeamArray.Num(); l++)
	{
		if (AttachedLaserBeamArray[l])
		{
			AttachedLaserBeamArray[l]->ToggleBeamActivation(true);
		}
	}
}
