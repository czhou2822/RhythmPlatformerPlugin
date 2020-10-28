// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "RPPEventBase.h"
#include "RPPPluginManager.h"

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

