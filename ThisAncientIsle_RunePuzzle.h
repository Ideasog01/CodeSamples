// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "RunePuzzle.generated.h"

UCLASS()
class ANCIENTISLE_API ARunePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARunePuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additonal Components")
	UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additonal Components")
	UStaticMeshComponent* CubeOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additonal Components")
	UStaticMeshComponent* CubeTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additonal Components")
	UStaticMeshComponent* CubeThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additonal Components")
	UStaticMeshComponent* CubeFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<int> CubeIndexArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<int> PatternIndexArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	AActor* GemToReveal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	USoundCue* PuzzleCompleteSfx = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateRuneCube(UStaticMeshComponent* HitMesh);

	bool PatternMatch();

};
