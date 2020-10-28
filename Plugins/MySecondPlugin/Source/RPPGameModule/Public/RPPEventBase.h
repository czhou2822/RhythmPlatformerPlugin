// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPPEventBase.generated.h"

UCLASS()
class RPPGAMEMODULE_API ARPPEventBase : public AActor
{
	GENERATED_BODY()

private:

	class ARPPPluginManager* RPPPluginManager;
	
public:	

	float AudioLocation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> SpawnedList;

	UPROPERTY(EditAnywhere)
	TArray<int32> SpawnPercentage;

	// Sets default values for this actor's properties
	ARPPEventBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
//#if WITH_EDITOR
	virtual void BeginDestroy() override;
//#endif

	virtual void SetAudioLocation();

	virtual void FindPluginManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	UFUNCTION()
	void DecideSpawnActor();

};
