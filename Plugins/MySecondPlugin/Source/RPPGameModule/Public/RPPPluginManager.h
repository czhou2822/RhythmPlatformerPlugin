// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPPPluginManager.generated.h"

UCLASS()
class RPPGAMEMODULE_API ARPPPluginManager : public AActor
{
	GENERATED_BODY()

private:
	
public:	

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRPPEventPlaced, AActor*);

	FOnRPPEventPlaced OnRPPEventPlaced;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRPPEventRemoved, int32);

	FOnRPPEventRemoved OnRPPEventRemoved;

	class UAudioComponent* PluginAudioPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPPPlugin")
	class USoundWave* AudioTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPPPlugin")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPPPlugin")
	float BPM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPPPlugin")
	float BeatStartingTime;



protected:

	// Sets default values for this actor's properties
	ARPPPluginManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
