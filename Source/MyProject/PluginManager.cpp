// Fill out your copyright notice in the Description page of Project Settings.
#include "PluginManager.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSource.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "MediaPlayerFacade.h"


// Sets default values
APluginManager::APluginManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	PluginAudioPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioPlayer"));
	//PluginAudioPlayer->SetupAttachment(RootComponent);

	RootComponent = PluginAudioPlayer;

	PluginAudioPlayer->SetUISound(false);
	PluginAudioPlayer->SetAutoActivate(false);

	PluginAudioPlayer->OnAudioPlaybackPercent.AddDynamic(this, &APluginManager::HandlePlaybackPercentageOnHit);



	MediaSoundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSoundComp"));
	MediaSoundComp->SetupAttachment(RootComponent);
	

}

void APluginManager::TestFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("PluginManager TestFunction Called"));

	if (PluginMediaPlayer && MediaSoundComp)
	{
		MediaSoundComp->SetMediaPlayer(PluginMediaPlayer);
		
		bool bOpenSuccess = PluginMediaPlayer->OpenSource(PluginMediaSource);
		UE_LOG(LogTemp, Warning, TEXT("OpenSuccess: %d"), bOpenSuccess);
		//TSharedPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> PlayerFacade = PluginMediaPlayer->GetPlayerFacade();


		//TSharedPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> PlayerFacade = MakeShared<FMediaPlayerFacade, ESPMode::ThreadSafe>();
		//PlayerFacade->Open(PluginMediaSource->GetUrl(), PluginMediaSource, nullptr);

		PluginMediaPlayer->OnMediaOpened.AddDynamic(this, &APluginManager::HandleOnMediaPlayerMediaOpened);
	}
}

void APluginManager::ChangePlaybackSpeed(float rate)
{
	if (PluginMediaPlayer)
	{
		PluginMediaPlayer->SetRate(rate);
	}
}


void APluginManager::PlaySoundFunction(float Start )
{

	//PluginAudioPlayer->Play(Start);
	//PluginMediaSoundComponent->GetMediaPlayer()->OpenSource(PluginMediaSource);
	UE_LOG(LogTemp, Warning, TEXT("Replay called Called"));


}

void APluginManager::HandlePlaybackPercentageOnHit(const USoundWave * PlayingSoundWave, const float PlaybackPercent)
{
	UE_LOG(LogTemp, Warning, TEXT("Responded to PercentageOnHit, Percentage: %f"), PlaybackPercent);
}

void APluginManager::HandleOnMediaPlayerMediaOpened(FString OpenedUrl)
{
	UE_LOG(LogTemp, Warning, TEXT("MediaOpened"));
	PluginMediaPlayer->Play();
}

// Called when the game starts or when spawned
void APluginManager::BeginPlay()
{
	Super::BeginPlay();
	PluginAudioPlayer->SetUISound(false);

	FVector MyCharacterLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	float Delta = (MyCharacterLocation.X - GetActorLocation().X) / (float)RunningSpeed;
	PluginAudioPlayer->Play(Delta);

	//UE_LOG(LogTemp, Warning, TEXT("Delta: %f"), Delta);
}

// Called every frame
void APluginManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



USoundWave* APluginManager::GetNormalSpeedAudio()
{
	return NormalSpeedAudio;
}

USoundWave* APluginManager::GetHalfSpeedAudio()
{
	return HalfSpeedAudio;
}

