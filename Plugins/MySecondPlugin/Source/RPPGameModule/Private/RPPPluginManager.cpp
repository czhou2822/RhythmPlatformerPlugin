// Fill out your copyright notice in the Description page of Project Settings.


#include "RPPPluginManager.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"

// Sets default values
ARPPPluginManager::ARPPPluginManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PluginAudioPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioPlayer"));

	PluginAudioPlayer->SetupAttachment(RootComponent);

	PluginAudioPlayer->SetUISound(false);
	PluginAudioPlayer->SetAutoActivate(false);

	if (AudioTrack)
	{
		PluginAudioPlayer->SetSound(AudioTrack);
	}


}

// Called when the game starts or when spawned
void ARPPPluginManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPPPluginManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

