// Fill out your copyright notice in the Description page of Project Settings.


//engine include
#include "Kismet/GameplayStatics.h"
#include "EditorViewportClient.h"
#include "Components/AudioComponent.h"

//user include
#include "RPPMain.h"
#include "RPPUtility.h"
#include "MySecondPluginManager.h"




BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SRPPMain::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::SelfHitTestInvisible);
	Initilization();
	ChildSlot
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			.Padding(FMargin(10.0,50.0,0.0,0.0))
			[
				SAssignNew(RPPButtonVBox, SRPPButtonVBox)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(RPPMainCanvas, SRPPMainCanvas)
			]
		];
}

void SRPPMain::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);


	//update look at
	{

		AudioCursor = (EditorViewportClient->GetViewLocation().X - CameraStartingLocation.X) / PluginManagerObject->RunningSpeed;
		AudioPercentage = AudioCursor / AudioDuration;
		SnaplineCursor = (AudioPercentage * URPPUtility::DataDrawArray.Num()) / 5;

		UE_LOG(LogTemp, Warning, TEXT("ViewLocationX: %.02f"), EditorViewportClient->GetViewLocation().X);
		UE_LOG(LogTemp, Warning, TEXT("AudioCursor: %.02f"), AudioCursor);
		UE_LOG(LogTemp, Warning, TEXT("AudioPercentage: %.02f"), AudioPercentage);
		UE_LOG(LogTemp, Warning, TEXT("SnaplineCursor: %i"), SnaplineCursor);

		UpdateCamaraLookAt();
	}



}

void SRPPMain::UpdateCamaraLookAt()
{
	if (EditorViewportClient)
	{
		FVector newLookAt = EditorViewportClient->GetViewLocation();

		float Delta = AudioCursor * PluginManagerObject->RunningSpeed;

		URPPUtility::RawDrawArrayToDrawArray(SnaplineCursor, 20000 + SnaplineCursor);

		EditorViewportClient->SetViewLocation(FVector(CameraStartingLocation.X + Delta, newLookAt.Y, newLookAt.Z));
	}
}

void SRPPMain::Initilization()
{
	//init variables
	{
		AudioCursor = 0.f;
		CameraStartingLocation = FVector(0,0,0);
	}

	//other init
	EditorViewportClient = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	if (EditorViewportClient)
	{
		CameraStartingLocation = EditorViewportClient->GetViewLocation();   //get default location of the camera, mainly for y and z as x will be override by tick shortly

		UWorld* World = EditorViewportClient->GetWorld();
		if (World)
		{
			TArray<AActor*> foundManager;
			UGameplayStatics::GetAllActorsOfClass(World, AMySecondPluginManager::StaticClass(), foundManager);


			if (foundManager.Num() == 1)
			{
				PluginManagerObject = Cast<AMySecondPluginManager>(foundManager[0]);
				//plugin manager related settings 
				if (PluginManagerObject)
				{
					if (USoundWave* SoundWave = (USoundWave*)PluginManagerObject->PluginAudioPlayer->Sound)
					{
						AudioDuration = SoundWave->Duration;
						//RPPUtil = NewObject<URPPUtility>();
						ProcessSoundWave(SoundWave);
					}
					ResetViewport();

				}
			}

		}
	}
}

void SRPPMain::ProcessSoundWave(USoundWave* InSoundWave)
{
	URPPUtility::SetDataRawArray(InSoundWave);
	URPPUtility::RawDataArrayToRawDrawArray(5);  //bucket size
	URPPUtility::RawDrawArrayToDrawArray(0, 20000);  //start, end
}

void SRPPMain::ResetViewport()
{
	AudioCursor = 0.f;

	if (EditorViewportClient)
	{
		EditorViewportClient->SetViewportType(ELevelViewportType::LVT_OrthoXZ);
		EditorViewportClient->SetViewMode(EViewModeIndex::VMI_Lit);
		CameraStartingLocation = FVector(PluginManagerObject->GetActorLocation().X, CameraStartingLocation.Y, CameraStartingLocation.Z);
		EditorViewportClient->SetViewLocation(CameraStartingLocation);
	}


}




END_SLATE_FUNCTION_BUILD_OPTIMIZATION
