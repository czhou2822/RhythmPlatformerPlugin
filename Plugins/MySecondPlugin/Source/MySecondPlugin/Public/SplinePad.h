// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePad.generated.h"

UCLASS()
class MYSECONDPLUGIN_API ASplinePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePad();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++")
	class USplineComponent* SplineComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
