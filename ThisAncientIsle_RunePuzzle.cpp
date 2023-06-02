#include "AncientIsle/Interactive/RunePuzzle.h"

// Sets default values
ARunePuzzle::ARunePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(RootComponent);

	CubeOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeOne"));
	CubeOne->SetupAttachment(MainMesh);
	
	CubeTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeTwo"));
	CubeTwo->SetupAttachment(MainMesh);

	CubeThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeThree"));
	CubeThree->SetupAttachment(MainMesh);

	CubeFour = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeFour"));
	CubeFour->SetupAttachment(MainMesh);
}

// Called when the game starts or when spawned
void ARunePuzzle::BeginPlay()
{
	Super::BeginPlay();

	if (GemToReveal)
	{
		GemToReveal->SetActorHiddenInGame(true);
		GemToReveal->SetActorEnableCollision(false);

		UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GemToReveal->GetRootComponent());
		Root->SetSimulatePhysics(false);
	}
	
}

// Called every frame
void ARunePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunePuzzle::RotateRuneCube(UStaticMeshComponent* HitMesh)
{
	if (PatternMatch()) //If the puzzle has already been solved, abort
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Rotate Rune Cube");
	HitMesh->AddLocalRotation(FRotator(0, 90, 0), true);

	//Find the index of the clicked on cube
	int CubeIndex = 0;

	if (HitMesh == CubeTwo)
	{
		CubeIndex = 1;
	}
	else if (HitMesh == CubeThree)
	{
		CubeIndex = 2;
	}
	else if (HitMesh == CubeFour)
	{
		CubeIndex = 3;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "HIT MESH DOES NOT MATCH!");
	}

	CubeIndexArray[CubeIndex]++;

	if(CubeIndexArray[CubeIndex] > 3)
	{
		CubeIndexArray[CubeIndex] = 0;
	}

	if(PatternMatch())
	{
		//Activate gem if the pattern matched
		if (GemToReveal)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Rune puzzle solved!");

			GemToReveal->SetActorHiddenInGame(false);
			GemToReveal->SetActorEnableCollision(true);
			
			UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GemToReveal->GetRootComponent());
			Root->SetSimulatePhysics(true);
			UGameplayStatics::PlaySound2D(this, PuzzleCompleteSfx);
		}
	}
}

bool ARunePuzzle::PatternMatch()
{
	int matchCount = 0;

	for (int i = 0; i < 4; i++) //Check each index of the rune cubes
	{
		if(CubeIndexArray[i] == PatternIndexArray[i])
		{
			matchCount++;
		}
	}


	//If all cubes matched, (a total of four cubes), return true
	return matchCount == 4;
}
