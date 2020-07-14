// Fill out your copyright notice in the Description page of Project Settings.
#define OUT 

#include "SMyCompoundWidget.h"
#include "DrawElements.h"
#include "SlateOptMacros.h"
#include "Misc/MessageDialog.h"
#include "MySecondPlugin.h"
#include "MySecondPluginManager.h"
#include "EngineUtils.h"
#include "LevelEditor.h"
#include "Engine/World.h"
#include "IAssetViewport.h"
#include "MySecondPluginTimestamp.h"
#include "MySecondPluginTextRW.h"
#include "Dom/JsonObject.h"
#include "AudioDevice.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SMyCompoundWidget::Construct(const FArguments& InArgs)
{
	Label = InArgs._Label;
	//ButtonClicked = InArgs._ButtonClicked;
	SMyCompoundWidget::InitializeMyCompoundWidget();
	SnapLine.Init(FVector2D(0,0), 2);


	ChildSlot
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()     //left side of screen
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Left)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()   //hidden button
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.Visibility(EVisibility::Hidden)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("Hidden Button")))
							]
						]
					+ SVerticalBox::Slot()   //pause/play
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::MyPauseAndPlay)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("Pause/Play")))
							]
						]
					+ SVerticalBox::Slot()   //reset cursor
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::Reset)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("Reset")))
							]
						]
					+ SVerticalBox::Slot()   //reload wave
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::ReloadWave)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("Reload")))
							]
						]
					+ SVerticalBox::Slot()   //mark
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::MarkTimeStamp)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("Mark")))
							]
						]
					+ SVerticalBox::Slot()   //set starting position
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::SetStartingPosition)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("SetStartingPosition")))
							]
						]
					+ SVerticalBox::Slot()   //replay speed
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SVerticalBox)
							+SVerticalBox::Slot()
							[
								SNew(SSlider)
								.Visibility(EVisibility::Visible)
								.OnControllerCaptureEnd(this, &SMyCompoundWidget::HandleOnSliderChanged)
								.MinValue(0.0f)
								.MaxValue(1.0f)
							]
							+ SVerticalBox::Slot()
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("ReplaySpeed")))
							]
						]
					+ SVerticalBox::Slot()   //  test button
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::TestFunction)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Visibility(EVisibility::Visible)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("TestButton")))
							]
						]
					+ SVerticalBox::Slot()   //  print text
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::SaveLevel)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Visibility(EVisibility::Visible)
							.Content()
							[
								SAssignNew(ButtonLabel, STextBlock)
								.Text(FText::FromString(TEXT("Save Level")))
							]
						]
					+ SVerticalBox::Slot()   // change text
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							[
								SNew(SButton)
								.OnClicked(this, &SMyCompoundWidget::LoadLevel)
								.OnHovered(this, &SMyCompoundWidget::MyHover)
								.Visibility(EVisibility::Visible)
								.Content()
								[
									SAssignNew(ButtonLabel, STextBlock)
									.Text(FText::FromString(TEXT("Load Level")))
								]
							]
						]

					+ SVerticalBox::Slot()   //  print text
						.VAlign(VAlign_Top)
						.HAlign(HAlign_Left)
						[
							SNew(SButton)
							.OnClicked(this, &SMyCompoundWidget::RefreshRunningSpeed)
							.OnHovered(this, &SMyCompoundWidget::MyHover)
							.Visibility(EVisibility::Visible)
							.Content()
								[
									SAssignNew(ButtonLabel, STextBlock)
									.Text(FText::FromString(TEXT("RefreshRunningSpeed")))
								]
						]

				]
		];
	bInitialFlag = true;
	PlaybackSpeed = 1.f;
	

}

void SMyCompoundWidget::HandleOnSliderChanged()
{
	UE_LOG(LogTemp, Log, TEXT("Changed!"));
}

void SMyCompoundWidget::InitializeMyCompoundWidget()
{
	if (bInitialFlag)
	{
		return;
	}
	MyEditorViewportClient = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	if (MyEditorViewportClient)
	{
		World = MyEditorViewportClient->GetWorld();
		MyEditorViewportClient->SetViewportType(ELevelViewportType::LVT_OrthoXZ);
		MyEditorViewportClient->SetViewMode(EViewModeIndex::VMI_Lit);
	}
	
	MyIAssetViewport = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor").GetFirstActiveViewport();
	CamaraStartLocation = MyEditorViewportClient->GetViewLocation();
	CamaraStartLocation.X = 0;

	
	
	SMyCompoundWidget::UpperBorderSize();
	SMyCompoundWidget::ReloadWave();

	MySecondPluginTextRW = NewObject<UMySecondPluginTextRW>();

}

FReply SMyCompoundWidget::ReloadWave()
{
	TArray<AActor*> foundManager;
	UGameplayStatics::GetAllActorsOfClass(World, AMySecondPluginManager::StaticClass(), foundManager);


	if (foundManager.Num() == 1)
	{
		PluginManagerObject = Cast<AMySecondPluginManager>(foundManager[0]);
		if (PluginManagerObject)
		{
			//PluginManagerObject->PluginAudioPlayer->SetSound(PluginManagerObject->GameAudio);
			MyAudioPlayer = PluginManagerObject->PluginAudioPlayer;

			MyAudioPlayer->SetUISound(true);
			MyAudioPlayer->Activate();
			bIsManagerValid = true;
			MyAudioPlayer->SetPaused(true);
			MySoundWave = (USoundWave*)MyAudioPlayer->Sound;

			MyAudioPlayer->OnAudioPlaybackPercentNative.AddSP(this, &SMyCompoundWidget::HandleOnAudioPlaybackPercentNative);

//			PluginManagerObject->PluginAudioPlayer->OnAudioPlaybackPercentNative.AddDynamic(this, &SMyCompoundWidget::HandleOnAudioPlaybackPercent);
//			WindowLength = (float) (NUMBER_OF_LINES_IN_WINDOW) / (float)RawDrawArray.Num() * (float)MySoundWave->Duration;
			BPM = 60.f;
			if (!MySoundWave)
			{
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Sound Not Set"));
				bIsManagerValid = false;
				return FReply::Handled();
			}
			MyEditorViewportClient->SetViewLocation(CamaraStartLocation);
			AudioDuration = MySoundWave->Duration;
			AudioCursor = 0;  //reset audio cursor
			AudioPercentage = 0;
			RawDataArray = SMyCompoundWidget::WaveToRawDataArray(MySoundWave); //load raw data to AudioWaveformDataArray
			SMyCompoundWidget::RawDataArrayToRawDrawArray(RawDataArray, ZoomFactor);
			PlayerRunningSpeed = PluginManagerObject->RunningSpeed;
			WindowLength = (NUMBER_OF_LINES_IN_WINDOW * ZoomFactor) / ((float)RawDataArray.Num()) * (float)MySoundWave->Duration;
			BorderUnitPerSecond = (float)BorderWidth /WindowLength ;
			UE_LOG(LogTemp, Warning, TEXT("Duration: %2.3f."), MySoundWave->Duration);
			UE_LOG(LogTemp, Warning, TEXT("Data size: %d."), MySoundWave->RawData.GetElementCount());
			UE_LOG(LogTemp, Warning, TEXT("WindowLength: %f."), WindowLength);

			
		}
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Manager Number Wrong"));
		bIsManagerValid = false;
	}

	return FReply::Handled();
}

FReply SMyCompoundWidget::Reset()
{
	AudioDuration = MySoundWave->Duration;
	AudioCursor = 0;  //reset audio cursor
	AudioPercentage = 0;
	MyEditorViewportClient->SetViewLocation(CamaraStartLocation);
	return FReply::Handled();

}

/**
 * Sets border position. Called when constructed. Updates @Borderbox
 *
 */
void SMyCompoundWidget::UpperBorderSize() 
{

	FVector2D InViewportSize;
	BoarderBox.Empty();
	
	if (MyIAssetViewport.IsValid())
	{
		InViewportSize = FVector2D(MyIAssetViewport->GetActiveViewport()->GetSizeXY());
	}
	else InViewportSize = FVector2D(0, 0);
	
	float ScaleFactor = 0.3;
	Padding = 50;
	BorderWidth = InViewportSize.X - 2 * Padding;
	BorderHeight = InViewportSize.Y * ScaleFactor;
	
	BorderUpperLeft = FVector2D (Padding, Padding);
	BorderUpperRight = BorderUpperLeft + FVector2D(BorderWidth, 0);
	BorderLowerRight = BorderUpperRight + FVector2D(0, BorderHeight);
	BorderLowerLeft = BorderUpperLeft + FVector2D (0, BorderHeight);

	// Inner Box
	
	

	BoarderBox.Add(BorderUpperLeft);
	BoarderBox.Add(BorderUpperRight);
	BoarderBox.Add(BorderLowerRight);
	BoarderBox.Add(BorderLowerLeft);
	BoarderBox.Add(BorderUpperLeft);

	
}


void SMyCompoundWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) // called everyframe and used for our gamelogic
{
	if (!bIsManagerValid)
	{
		return;
	}
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	SMyCompoundWidget::UpperBorderSize();
	SMyCompoundWidget::UpdateSnapLine();

	if ((!MyAudioPlayer->bIsPaused) && (AudioPercentage <= 1))
	{
		AudioCursor += InDeltaTime * (float)PlaybackSpeed;
	}
	else
	{
		AudioCursor = (MyEditorViewportClient->GetViewLocation().X - CamaraStartLocation.X) / PluginManagerObject->RunningSpeed;
	}


	AudioPercentage = AudioCursor / AudioDuration;
	SnapLineCursor = (AudioPercentage * RawDataArray.Num()) / ZoomFactor;

	SMyCompoundWidget::UpdateCamaraLookAt();

	//FActiveSound* ActiveSound = MyAudioPlayer->GetAudioDevice()->FindActiveSound(MyAudioPlayer->GetAudioComponentID());
	//UE_LOG(LogTemp, Warning, TEXT("Playback sound: %s"), *FString::SanitizeFloat( ActiveSound->PlaybackTime));

}

void SMyCompoundWidget::UpdateCamaraLookAt()
{
	if (MyEditorViewportClient)
	{
		CamaraLocation = MyEditorViewportClient->GetViewLocation();
		
		int Delta = AudioCursor * PluginManagerObject->RunningSpeed;


		SMyCompoundWidget::RawDrawArrayToDrawArray(SnapLineCursor, NUMBER_OF_LINES_IN_WINDOW + SnapLineCursor, RawDrawArray);
		//MyEditorViewportClient->SetViewLocation(CamaraStartLocation + FVector(Delta, 0, 0));


		MyEditorViewportClient->SetViewLocation(FVector(CamaraStartLocation.X + Delta, CamaraLocation.Y, CamaraLocation.Z));
	}
}

FReply SMyCompoundWidget::OnMouseMove(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	SWidget::OnMouseMove(MyGeometry, MouseEvent);
	return FReply::Unhandled();
}

FReply SMyCompoundWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "works");
	return FReply::Handled();
}

void SMyCompoundWidget::UpdateSnapLine()
{
	SnapLine[0] = (BorderUpperLeft + BorderUpperRight) / 2;
	SnapLine[1] = SnapLine[0] + FVector2D(0,3000);		
}


int32 SMyCompoundWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements,	int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
		FSlateDrawElement::MakeLines(OutDrawElements,    //render border 
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			BoarderBox,
			ESlateDrawEffect::None, 
			FLinearColor::White,
			true, 
			1.f
		);


		FSlateDrawElement::MakeLines(OutDrawElements,    //render snapline 
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			SnapLine,
			ESlateDrawEffect::None,
			FLinearColor::Red,
			true,
			2.f
		);



		FSlateDrawElement::MakeLines(OutDrawElements,   //render waveform
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			DrawArray,
			ESlateDrawEffect::None,
			FLinearColor::Yellow,
			true,
			0.5f
		);

		//SnapLineCursor
		//SMyCompoundWidget::GetBeatGrid(AudioCursor, AllottedGeometry, OutDrawElements, LayerId);


	return   SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

FReply SMyCompoundWidget::MyPauseAndPlay()
{
	//AudioCursor = AudioCursor * PlaybackSpeed;
	if (MyAudioPlayer->bIsPaused)
	{
		MyAudioPlayer->Play(AudioCursor);
		MyAudioPlayer->SetPaused(!MyAudioPlayer->bIsPaused);
	}
	else
	{
		MyAudioPlayer->SetPaused(!MyAudioPlayer->bIsPaused);
	}


	return FReply::Handled();
}

FReply SMyCompoundWidget::MarkTimeStamp()
{
	AMySecondPluginTimestamp* newTimeStamp = World->SpawnActor<AMySecondPluginTimestamp>(FVector(MyEditorViewportClient->GetViewLocation().X, 0, MyEditorViewportClient->GetViewLocation().Z), FRotator::ZeroRotator);

	FPlatformerEvent NewEvent;
	NewEvent.EventName = newTimeStamp->GetName();
	NewEvent.EventTime = AudioCursor;


	MySecondPluginTextRW-> AddNewEvent(NewEvent);
	

	return FReply::Handled();
}

FReply SMyCompoundWidget::ChangePlaybackRate()
{
	if (PlaybackSpeed == 1)
	{
		PlaybackSpeed = 0.5f;
	}
	else
	{
		PlaybackSpeed = 1.f;
	}

	MyAudioPlayer->SetPitchMultiplier(PlaybackSpeed);



	return FReply::Handled();
}

FReply SMyCompoundWidget::TestFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("SCompoundWidget TestFunction!!!!"));

	

	return FReply::Handled();
}

void SMyCompoundWidget::HandleOnAudioPlaybackPercentNative(const class UAudioComponent* AudioComponent, const class USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
	UE_LOG(LogTemp, Warning, TEXT("PluginPlayback: %s. Percent: %s"), *PlayingSoundWave->GetName(), *FString::SanitizeFloat(PlaybackPercent));
}

FReply SMyCompoundWidget::LoadLevel()
{
	FString outString;
	MySecondPluginTextRW->LoadLevelInfo(TEXT("test.txt"), outString);

	

	return FReply::Handled();
}

FReply SMyCompoundWidget::SaveLevel()
{


	MySecondPluginTextRW->SaveLevelInfo("test.txt");

	return FReply::Handled();
}

FReply SMyCompoundWidget::RefreshRunningSpeed()
{
	//UE_LOG(LogTemp, Warning, TEXT("Running Speed: %s. "), *FString::SanitizeFloat(PluginManagerObject->RunningSpeed));
	
	//UE_LOG(LogTemp, Warning, TEXT("Running Speed: %d. "), MySecondPluginTextRW->EventMemo.Num());

	TSubclassOf<AMySecondPluginTimestamp> classToFind;
	classToFind = AMySecondPluginTimestamp::StaticClass();
	TArray<AActor*> FoundMarkers;
	UGameplayStatics::GetAllActorsOfClass(World, classToFind, FoundMarkers);


	for (FPlatformerEvent Event : MySecondPluginTextRW->EventMemo)
	{
		FActorSpawnParameters SpawnParms;
		SpawnParms.Name = FName(*Event.EventName);
		FVector SpawnLocation = FVector(Event.EventTime * PluginManagerObject->RunningSpeed, 0, MyEditorViewportClient->GetViewLocation().Z);


		bool bIsActorFound = false;
		for (AActor* SingleActor : FoundMarkers)
		{
			if (SingleActor->GetName() == Event.EventName)
			{
				SingleActor->SetActorLocation(SpawnLocation);
				bIsActorFound = true;
				break;
			}
		}
		if (!bIsActorFound)
		{
			AMySecondPluginTimestamp* newTimeStamp = World->
				SpawnActor<AMySecondPluginTimestamp>(SpawnLocation, FRotator::ZeroRotator, SpawnParms);
		}
	}


	
	return FReply::Handled();
}

FReply SMyCompoundWidget::SetStartingPosition() 
{
	CamaraStartLocation = MyEditorViewportClient->GetViewLocation();
	return FReply::Handled();
}

void SMyCompoundWidget::MyHover()
{
	//ButtonLabel->SetText(FString(TEXT("Hovered!")));
}

USoundWave * SMyCompoundWidget::AudiofileLoader(int Selection)  //load wave to *usoundwave
{
	
	FString dir = FPaths::ProjectDir();
	dir = dir + "Content/AudioFile";
	
	UE_LOG(LogTemp, Warning, TEXT("Directory exists? %s."), FPaths::DirectoryExists(dir)? "T" : "F");

	dir = dir + "/1.wav";
	UE_LOG(LogTemp, Warning, TEXT("File dir: %s. Exist: %s. "), *dir, FPaths::FileExists(dir)? "T" : "F");

	USoundWave* swRef;


	UObject* objFinder = nullptr;

	if (Selection == 1)
	{
		objFinder = StaticLoadObject(USoundWave::StaticClass(), nullptr, TEXT("SoundWave'/Game/AudioFile/1.1'"), *dir);
	}

	else 
	{
		objFinder = StaticLoadObject(USoundWave::StaticClass(), nullptr, TEXT("SoundWave'/Game/AudioFile/2.2'"), *dir);
	}

	swRef = dynamic_cast <USoundWave*> (objFinder);
			

	return swRef;
}

void SMyCompoundWidget::CheckWaveformData(uint8 * InputArray)
{
	for (int i = 0; i < MySoundWave->RawPCMDataSize; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Duration: %d."), MySoundWave->RawPCMDataSize);
	}
	
	TArray<TArray<float>> OutAmplitudes;

	RawDataArray = SMyCompoundWidget::WaveToRawDataArray(MySoundWave);

	UE_LOG(LogTemp, Warning, TEXT("USoundWaveCount: %d."), MySoundWave->RawData.GetElementCount());
	UE_LOG(LogTemp, Warning, TEXT("OutAmplitudesCount: %d."), RawDataArray.Num());


	
}

/**
 Extract data from USoundWave and put them into RawDataArray
 @param Soundwave, the Soundwave pointer
 @return TArray containing raw data from the USoundWave object. 
*/
TArray<float> SMyCompoundWidget::WaveToRawDataArray(USoundWave * SoundWave)
{
	TArray<float> Output;
	const int32 NumChannels = SoundWave->NumChannels;

	if ((NumChannels == 0) || (SoundWave->RawData.GetBulkDataSize() == 0))
	{
		return Output;
	}

	uint8* RawWaveData = (uint8*)SoundWave->RawData.Lock(LOCK_READ_ONLY);
	int32 RawDataSize = SoundWave->RawData.GetBulkDataSize();
	FWaveModInfo WaveInfo;
	
	if (WaveInfo.ReadWaveHeader(RawWaveData, RawDataSize, 0))
	{
		uint32 SampleCount = WaveInfo.SampleDataSize / (2 * NumChannels);

		const int16* SamplePtr = reinterpret_cast<const int16*>(WaveInfo.SampleDataStart);
		
		for (uint32 SampleIndex = 0; SampleIndex < SampleCount; ++SampleIndex)   
		{
			int64 SampleSum = 0;
			for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)  
			{
				SampleSum += (*SamplePtr);
				SamplePtr++;
			}
			SampleSum = SampleSum / (float)NumChannels;
			Output.Add(SampleSum);
		}
	}

	SoundWave->RawData.Unlock();

	return Output;
}

/*
 Extract raw data from RawDataArray and put them into RawDrawArray
 @param InputArray, the RawDataArray from USoundWave
 @param BucketSize, we only push the absolute max value in the bucket into the DrawArray.
 Therefore, by default, the size of RawDrawArray is (InputArray.size()/200)
*/
void SMyCompoundWidget::RawDataArrayToRawDrawArray(const TArray<float>& InputArray, int BucketSize )
{
	RawDrawArray.Empty();
	float YOffset = Padding + BorderHeight / 2.f;
	int InputArrayIndex = 0;
	int NumberOfBuckets = (InputArray.Num() - (InputArray.Num() % BucketSize)) / BucketSize;
	float AbsMax = InputArray[0];
	for (int i = 0; i < InputArray.Num(); i++)
	{
		if (FMath::Abs(InputArray[i]) > AbsMax)
		{
			AbsMax = InputArray[i];
		}
	}
	float YScale = BorderHeight / (2 * AbsMax);
	for (int i = 0; i < NumberOfBuckets; i++)
	{
		float Temp = 0;

		for (int j = 0; j < BucketSize; j++)      //absmax with bucket
		{
			if (FMath::Abs(InputArray[InputArrayIndex]) > Temp)
			{
				Temp = InputArray[InputArrayIndex];
			}
			InputArrayIndex++;
		}


		Temp = YOffset - (Temp * YScale);

		RawDrawArray.Add(Temp);

	}


}

/**
 Extract raw data from RawDataArray and put them into TArray<float> for drawing
 @param InputArray, the RawDataArray from USoundWave
 @param SampleCount, how many samples to draw. For example, If InputArray contains 20K samples, 
 putting 10k at this para will only draw half of the waveform of the file
 @param BucketSize, we only push the absolute max value in the bucket into the DrawArray. 
 Therefore, by default, the size of DrawArray is (InputArray.size()/200)
*/
void SMyCompoundWidget::RawDrawArrayToDrawArray(int Start, const int End, TArray<float>& InArrayToBeDrew)
{
	//get # of steps
	//take the peak value of each bucket
	//add to array
	/*
	This function serves as a moving window of deciding what's shown on the screen, picking the "window" section out of RawDrawArray
	if (header-start)<0 -> window is larger than default 
	if (header-start)>0  &&  if (end+tail)<InArray.num() -> still going

	if (end+tail)>InArray.num() -> fill default

	//Todo: is it possible to change the pointer to the array instead of rewritting the array every frame? 

	*/



	DrawArray.Empty();
	int ArrayIndex = Start;										 //starting point of the InArray
	int Steps = 1;												//how many steps has been taken. This process always take NUMBER_OF_LINES_IN_WINDOW steps
	int NumberOfSteps = NUMBER_OF_LINES_IN_WINDOW;		
	float YOffset = Padding + BorderHeight / 2.f;				//default Y position, horizontal line
	float XCord = Padding;										//X  starting cord   //Todo, just change Y, leave X
	float XIncrement = (float)BorderWidth / NumberOfSteps;		
	int Header = NUMBER_OF_LINES_IN_WINDOW/2;
	int Tail = NUMBER_OF_LINES_IN_WINDOW/2;
	
	EDrawType NextDrawType = EDrawType::Header;
	
	int HeadNeeded = Header - Start;
	if (HeadNeeded >= 0)
	{
		ArrayIndex = 0;
	}
	else
	{
		NextDrawType = EDrawType::Data;
		ArrayIndex = ArrayIndex - NumberOfSteps/2;
		if (ArrayIndex < 0) ArrayIndex = 0;
	}



	while (Steps < NumberOfSteps)
	{
		float YTemp = YOffset;
		switch (NextDrawType)
		{
			case EDrawType::Data:
			{
				/*
				if array index in range, fill
				else mark next as footer and break;
				*/

				if (ArrayIndex > InArrayToBeDrew.Num() - 1)
				{
					NextDrawType = EDrawType::Footer;
					break;
				}

				YTemp = InArrayToBeDrew[ArrayIndex];
				ArrayIndex++;
				break;
			}
			case EDrawType::Header:
			{
				/*
				if (headneeded<0), break, nexttype = data
				else fill head, headneede--;
				*/
				if (HeadNeeded <= 0)
				{
					NextDrawType = EDrawType::Data;
					break;
				}
				else
				{
					HeadNeeded--;
				}
				break;
			}
			case EDrawType::Footer:
			{
				/*
				fill tail, the while take cares of ending condition
				*/
				break;
			}
		}
		DrawArray.Add(FVector2D(XCord, YTemp));
		XCord += XIncrement;
		Steps++;
	}
}

/*given a point, it calculates the beat grid in that window. 
For example, if there's beat at 3s and the window is 5s, it calculates the beat. 
Called every frames. */

void SMyCompoundWidget::GetBeatGrid(float CurrentCursor, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const //CurrentCorsor feeds audiocursor
{
	float  Border = 0;

	int32 StartingIndex = 1;	
	int32 LastXCord = Padding;
	float LowerBound = CurrentCursor - WindowLength / 2; //where beat grid starts to render. -> left side of the screen. 
	if (CurrentCursor - WindowLength / 2 < WindowLength / 2)  //if cursor is less than half of window length, that means window is fill with head. No beat should be rendered.
	{
	//	return;
	}

	if (CurrentCursor < WindowLength / 2) //header presented
	{
		Border = CurrentCursor + WindowLength / 2;
		LastXCord = LastXCord + (WindowLength / 2 - CurrentCursor) * BorderUnitPerSecond;
	}
	else if (CurrentCursor > AudioDuration)  //cursor is beyond audio file
	{
		return;
	}
	else                                        //default
	{
		Border = CurrentCursor + WindowLength / 2;
		while ((RawBeatArray[StartingIndex] < (LowerBound)) && (StartingIndex < RawBeatArray.Num()))
		{
			StartingIndex++;
		}

		LastXCord = LastXCord + (RawBeatArray[StartingIndex - 1] - (LowerBound)) * BorderUnitPerSecond;
		
	}
	

     

	while ((RawBeatArray[StartingIndex] < Border) && (StartingIndex < RawBeatArray.Num()))
	{
		float XCord = LastXCord + (RawBeatArray[StartingIndex] - RawBeatArray[StartingIndex - 1]) * BorderUnitPerSecond;

		FSlateDrawElement::MakeLines(OutDrawElements,    //render beat grid one by one
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			{ FVector2D(XCord, Padding), FVector2D(XCord, Padding + 500) },
			ESlateDrawEffect::None,
			FLinearColor::Green,
			true,
			0.5
		);


		StartingIndex++;
		//if (StartingIndex > RawBeatArray.Num())
		//{
		//	return;
		//}

		LastXCord = XCord;

	}
	
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION
