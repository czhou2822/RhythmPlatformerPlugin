// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySecondPluginManager.generated.h"

class UAudioComponent;
class USoundWave;




UCLASS()
class MYSECONDPLUGIN_API AMySecondPluginManager : public AActor
{
	GENERATED_BODY()



	
public:	
	// Sets default values for this actor's properties
	AMySecondPluginManager();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UAudioComponent* PluginAudioPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* GameAudio;




	//UPROPERTY(EditAnywhere, Category = "Experimental")
	//	UMediaPlayer* PluginMediaPlayer;

	//UPROPERTY(EditAnywhere, Category = "Experimental")
	//	UMediaSoundComponent* MediaSoundComp;

	//UPROPERTY(EditAnywhere, Category = "Experimental")
	//	UMediaSource* PluginMediaSource;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnComponentActivated( UActorComponent* Component, bool bReset);

	UFUNCTION()
	void HandleOnPlaybackPercent(const USoundWave* PlayingWave, const float PlaybackPercent);

	UFUNCTION()
	void HandleOnAudioFinished();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void TestFunction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunningSpeed;

	UFUNCTION(BlueprintCallable)
		void PlaySoundFunction(float Start = 0);

	UFUNCTION()
		void HandleOnAudioFinishedNative(const class UAudioComponent* AudioComp, const class USoundWave* SoundWave, const float PlaybackPercent);

	UFUNCTION(BlueprintCallable)
		void ChangePlaybackSpeed(float rate);


	USoundWave* GetAudio();

};
