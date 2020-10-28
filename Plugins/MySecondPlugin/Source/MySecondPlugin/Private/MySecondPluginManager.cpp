//// Fill out your copyright notice in the Description page of Project Settings.
//#include "MySecondPluginManager.h"
//#include "EngineUtils.h"
//#include "Engine.h"
//#include "Kismet/GameplayStatics.h"
//#include "Components/AudioComponent.h"
//#include "Sound/SoundWave.h"
//#if PLATFORM_WINDOWS
//#pragma optimize("", off)
//#endif
//
//
//
//// Sets default values
//AMySecondPluginManager::AMySecondPluginManager()
//{
//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	PluginAudioPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioPlayer"));
//
//	PluginAudioPlayer->SetupAttachment(RootComponent);
//
//	PluginAudioPlayer->SetUISound(false);
//	PluginAudioPlayer->SetAutoActivate(false);
//
//
//	PluginAudioPlayer->OnAudioFinished.AddDynamic(this, &AMySecondPluginManager::HandleOnAudioFinished);
//	PluginAudioPlayer->OnComponentActivated.AddDynamic(this, &AMySecondPluginManager::HandleOnComponentActivated);
//
//	PluginAudioPlayer->OnAudioPlaybackPercent.AddDynamic(this, &AMySecondPluginManager::HandleOnPlaybackPercent);
//		
//
//
//}
//
//// Called when the game starts or when spawned
//void AMySecondPluginManager::BeginPlay()
//{
//	Super::BeginPlay();
//	PluginAudioPlayer->SetUISound(false);
//
//	FVector MyCharacterLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
//
//
//
//	float Delta = (MyCharacterLocation.X - GetActorLocation().X) / (float)RunningSpeed;
//	//PluginAudioPlayer->Play(Delta);
//
//	//UE_LOG(LogTemp, Warning, TEXT("Delta: %f"), Delta);
//}
//
//void AMySecondPluginManager::HandleOnPlaybackPercent(const USoundWave* PlayingSoundWave, const float PlaybackPercent)
//{
//	//float CurrentPlaybackTime = PlayingWave->Duration * PlaybackPercent;
//	UE_LOG(LogTemp, Warning, TEXT("ActorPlayback: %s. Percent: %s"), *PlayingSoundWave->GetName(), *FString::SanitizeFloat(PlaybackPercent));
//}
//
//
//void AMySecondPluginManager::HandleOnAudioFinished()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Audio Finished"));
//
//}
//
//void AMySecondPluginManager::HandleOnAudioFinishedNative(const UAudioComponent* AudioComp, const USoundWave* SoundWave, const float PlaybackPercent)
//{
//	UE_LOG(LogTemp, Warning, TEXT("OnMusicPlayback: %s. "), *FString::SanitizeFloat(PlaybackPercent));
//}
//
//void AMySecondPluginManager::TestFunction()
//{
//	UE_LOG(LogTemp, Warning, TEXT("MySecondPluginManager TestFunction Called"));
//
//	PluginAudioPlayer->Play();
//
//}
//
//void AMySecondPluginManager::ChangePlaybackSpeed(float rate)
//{
//
//}
//
//
//void AMySecondPluginManager::PlaySoundFunction(float Start)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Replay called Called"));
//}
//
//
//
//
//
//
//void AMySecondPluginManager::HandleOnComponentActivated(UActorComponent* Component, bool bReset)
//{
//	UE_LOG(LogTemp, Warning, TEXT("HandleOnActivated: %s. "), *Component->GetName());
//}
//
//// Called every frame
//void AMySecondPluginManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//
//
//
//
//
//#if PLATFORM_WINDOWS
//#pragma optimize("", on)
//#endif
