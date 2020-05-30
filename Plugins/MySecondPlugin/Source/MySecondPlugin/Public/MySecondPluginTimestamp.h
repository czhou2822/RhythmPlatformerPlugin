// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "MySecondPluginTimestamp.generated.h"

class USphereComponent;

UCLASS()
class MYSECONDPLUGIN_API AMySecondPluginTimestamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySecondPluginTimestamp();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> SpawnedList;

	UPROPERTY(EditAnywhere)
	TArray<int32> SpawnPercentage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnActorBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void DecideSpawnActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
