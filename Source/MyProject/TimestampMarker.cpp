// Fill out your copyright notice in the Description page of Project Settings.


#include "TimestampMarker.h"

// Sets default values
ATimestampMarker::ATimestampMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATimestampMarker::BeginPlay()
{
	Super::BeginPlay();
	//ActorLocation = GetActorLocation();
	//AnActor->GetClass();
	//AnActor = GetWorld()->SpawnActor<AActor>(AnActor->GetClass(), GetActorLocation());
	
}

// Called every frame
void ATimestampMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

