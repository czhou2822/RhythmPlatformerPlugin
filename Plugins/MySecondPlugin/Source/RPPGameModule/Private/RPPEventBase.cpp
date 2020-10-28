// Fill out your copyright notice in the Description page of Project Settings.
#include "RPPEventBase.h"
#include "RPPPluginManager.h"

#include "Kismet/GameplayStatics.h"


#if WITH_EDITOR
//#include "MySecondPlugin/Public/RPPUtility.h"

#endif


// Sets default values
ARPPEventBase::ARPPEventBase()
	:RPPPluginManager(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ARPPEventBase::BeginPlay()
{
	Super::BeginPlay();
	
#if WITH_EDITOR

	//URPPUtility::TestFunction();

#endif
	
}

//#if WITH_EDITOR
void ARPPEventBase::BeginDestroy()
{
	Super::BeginDestroy();
	if (GetWorld())
	{
		if (RPPPluginManager)
		{
			RPPPluginManager->OnRPPEventRemoved.Broadcast(GetUniqueID());
		}
		UE_LOG(LogTemp, Warning, TEXT("Event %i destroy"), GetUniqueID());
	}
}
void ARPPEventBase::SetAudioLocation()
{
	if (RPPPluginManager)
	{
		AudioLocation = (GetActorLocation().X - RPPPluginManager->GetActorLocation().X) / RPPPluginManager->RunningSpeed;
	}
	else
	{
		FindPluginManager();
	}

	UE_LOG(LogTemp, Warning, TEXT("Event %i audioLocation: %s"), GetUniqueID(), *FString::SanitizeFloat(AudioLocation,2));

}
void ARPPEventBase::FindPluginManager()
{
	if (GetWorld())
	{
		TArray<AActor*> foundManager;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARPPPluginManager::StaticClass(), foundManager);

		if (foundManager.Num() == 1)
		{
			RPPPluginManager = Cast<ARPPPluginManager>(foundManager[0]);
			SetAudioLocation();
		}
	}
}
//#endif

void ARPPEventBase::OnConstruction(const FTransform& Transform)
{

	if (GetWorld())
	{
		if (RPPPluginManager)
		{
			RPPPluginManager->OnRPPEventPlaced.Broadcast(this);
			SetAudioLocation();
		}
		else
		{
			FindPluginManager();
		}
	}

}

// Called every frame
void ARPPEventBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPPEventBase::DecideSpawnActor()
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

