// Fill out your copyright notice in the Description page of Project Settings.

#include "MySecondPluginTimestamp.h"
#include "components/SphereComponent.h"

// Sets default values
AMySecondPluginTimestamp::AMySecondPluginTimestamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->AttachTo(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//RootComponent = SphereComp;
	RootComponent = SphereComp;

	SphereMesh->SetupAttachment(RootComponent);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMySecondPluginTimestamp::HandleOnActorBeginOverlap);
}

// Called when the game starts or when spawned
void AMySecondPluginTimestamp::BeginPlay()
{
	Super::BeginPlay();
	DecideSpawnActor();
}

void AMySecondPluginTimestamp::HandleOnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Timestamp Overlapped"));
}

void AMySecondPluginTimestamp::DecideSpawnActor()
{
	TArray <int> SpawnList;
	SpawnList.Init(-1, 100);
	int32 SpawnListIndex = 0;

	for (int32 j = 0; j < SpawnPercentage.Num(); j++)
	{
		for (int32 i = SpawnListIndex; i < SpawnListIndex + SpawnPercentage[j]; i++)
		{
			SpawnList[i] = j;
		}
		SpawnListIndex += SpawnPercentage[j];
	}

	int SpawnIndex = FMath::RandRange(0, 99);

	UE_LOG(LogTemp, Warning, TEXT("SpawnIndex: %d"), SpawnList[SpawnIndex]);
	UE_LOG(LogTemp, Warning, TEXT("SpawnIndex: %s"), *SpawnedList[SpawnList[SpawnIndex]]->StaticClass()->GetFName().ToString());
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<TSubclassOf<AActor>> SpawnedList;

	GetWorld()->SpawnActor<AActor>(SpawnedList[SpawnList[SpawnIndex]], GetActorLocation(), FRotator(0, 0, 0));


}

// Called every frame
void AMySecondPluginTimestamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

