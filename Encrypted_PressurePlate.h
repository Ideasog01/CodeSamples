#pragma once

#include "CoreMinimal.h"
#include "Encrypted/Interactive/InteractiveObject.h"
#include "PressurePlate.generated.h"

class ADoor;
class ALaserBeam;

/**
 * 
 */
UCLASS()
class ENCRYPTED_API APressurePlate : public AInteractiveObject
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Attached Objects")
	TArray<ADoor*> AttachedDoorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Attached Objects")
	TArray<ALaserBeam*> AttachedLaserBeamArray;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	virtual void BeginPlay() override;
};
