// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "PluginManager.generated.h"

class UMediaPlayer;
class UMediaSoundComponent;
class UMediaSource;

UCLASS(Blueprintable)
class MYPROJECT_API APluginManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APluginManager();

	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* PluginAudioPlayer;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* NormalSpeedAudio;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* HalfSpeedAudio;
	



	UPROPERTY(EditAnywhere, Category = "Experimental")
	UMediaPlayer* PluginMediaPlayer;

	UPROPERTY(EditAnywhere, Category = "Experimental")
	UMediaSoundComponent* MediaSoundComp;

	UPROPERTY(EditAnywhere, Category = "Experimental")
	UMediaSource* PluginMediaSource;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TestFunction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunningSpeed = 600;

	UFUNCTION(BlueprintCallable)
	void PlaySoundFunction(float Start=0);

	UFUNCTION()
	void HandlePlaybackPercentageOnHit(const USoundWave* PlayingSoundWave, const float PlaybackPercent);

	UFUNCTION()
	void HandleOnMediaPlayerMediaOpened(FString OpenedUrl);


	UFUNCTION(BlueprintCallable)
	void ChangePlaybackSpeed(float rate);


	USoundWave* GetNormalSpeedAudio();
	USoundWave* GetHalfSpeedAudio();


protected:


	bool bHiddenEd = false;



};
