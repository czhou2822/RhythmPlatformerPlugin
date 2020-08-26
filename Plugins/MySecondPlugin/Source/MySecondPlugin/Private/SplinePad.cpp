// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePad.h"
#include "Components/SplineComponent.h"
// Sets default values
ASplinePad::ASplinePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));

}

// Called when the game starts or when spawned
void ASplinePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplinePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

