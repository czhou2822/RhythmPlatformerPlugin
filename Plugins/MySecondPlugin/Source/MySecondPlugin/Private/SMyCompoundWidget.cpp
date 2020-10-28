//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "SMyCompoundWidget.h"
//#include "DrawElements.h"
//#include "SlateOptMacros.h"
//#include "Misc/MessageDialog.h"
//#include "MySecondPlugin.h"
//#include "MySecondPluginManager.h"
//#include "EngineUtils.h"
//#include "LevelEditor.h"
//#include "Engine/World.h"
//#include "IAssetViewport.h"
//#include "MySecondPluginTimestamp.h"
//#include "MySecondPluginTextRW.h"
//#include "Dom/JsonObject.h"
//#include "AudioDevice.h"
//#include "Containers/Array.h"
//
//#if PLATFORM_WINDOWS
//#pragma optimize("", on)
//#endif
//
//
//
//BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
//
//void SMyCompoundWidget::Construct(const FArguments& InArgs)
//{
//	Label = InArgs._Label;
//	//ButtonClicked = InArgs._ButtonClicked;
//	SMyCompoundWidget::InitializeMyCompoundWidget();
//	SnapLine.Init(FVector2D(0,0), 2);
//
//
//	ChildSlot
//		.VAlign(VAlign_Top)
//		.HAlign(HAlign_Left)
//		[
//			SNew(SOverlay)
//			+ SOverlay::Slot()     //left side of screen
//				.VAlign(VAlign_Top)
//				.HAlign(HAlign_Left)
//				[
//					SNew(SVerticalBox)
//					+ SVerticalBox::Slot()   //hidden button
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.Visibility(EVisibility::Hidden)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("Hidden Button")))
//							]
//						]
//					+ SVerticalBox::Slot()   //pause/play
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::MyPauseAndPlay)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("Pause/Play")))
//							]
//						]
//					+ SVerticalBox::Slot()   //reset cursor
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::Reset)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("Reset")))
//							]
//						]
//					+ SVerticalBox::Slot()   //reload wave
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::ReloadWave)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("Reload")))
//							]
//						]
//					+ SVerticalBox::Slot()   //mark
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::MarkTimeStamp)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("Mark")))
//							]
//						]
//					+ SVerticalBox::Slot()   //set starting position
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::SetStartingPosition)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("SetStartingPosition")))
//							]
//						]
//					+ SVerticalBox::Slot()   //replay speed
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SVerticalBox)
//							+SVerticalBox::Slot()
//							[
//								SNew(SSlider)
//								.Visibility(EVisibility::Visible)
//								.OnValueChanged(this, &SMyCompoundWidget::HandleOnSliderChanged)
//								.MinValue(0.0f)
//								.MaxValue(1.0f)
//							]
//							+ SVerticalBox::Slot()
//							[
//								SNew(STextBlock)
//								.Text(FText::FromString(TEXT("ReplaySpeed")))
//							]
//						]
//					+ SVerticalBox::Slot()   //  test button
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::TestFunction)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Visibility(EVisibility::Visible)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("TestButton")))
//							]
//						]
//					+ SVerticalBox::Slot()   //  Save Level
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::SaveLevel)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Visibility(EVisibility::Visible)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("Save Level")))
//							]
//						]
//					+ SVerticalBox::Slot()   // Load Level
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SHorizontalBox)
//							+ SHorizontalBox::Slot()
//							[
//								SNew(SButton)
//								.OnClicked(this, &SMyCompoundWidget::LoadLevel)
//								.OnHovered(this, &SMyCompoundWidget::MyHover)
//								.Visibility(EVisibility::Visible)
//								.Content()
//								[
//									SAssignNew(ButtonLabel, STextBlock)
//									.Text(FText::FromString(TEXT("Load Level")))
//								]
//							]
//						]
//
//					+ SVerticalBox::Slot()   //  print text
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::RefreshRunningSpeed)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Visibility(EVisibility::Visible)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("RefreshRunningSpeed")))
//							]
//						]
//					+ SVerticalBox::Slot()   //  print text
//						.VAlign(VAlign_Top)
//						.HAlign(HAlign_Left)
//						[
//							SNew(SButton)
//							.OnClicked(this, &SMyCompoundWidget::ChangeBeatStartingTime)
//							.OnHovered(this, &SMyCompoundWidget::MyHover)
//							.Visibility(EVisibility::Visible)
//							.Content()
//							[
//								SAssignNew(ButtonLabel, STextBlock)
//								.Text(FText::FromString(TEXT("LetBeatStartsHere")))
//							]
//						]
//
//				]
//		];
//	bInitialFlag = true;
//	PlaybackSpeed = 1.f;
//	
//
//}
//
//void SMyCompoundWidget::HandleOnSliderChanged(float InFloat)
//{
//	UE_LOG(LogTemp, Log, TEXT("Changed! %s"), *FString::SanitizeFloat(InFloat));
//	ChangePlaybackRate(InFloat);
//}
//
//FReply SMyCompoundWidget::ChangeBeatStartingTime()
//{
//	BeatStartingTime = AudioCursor;
//
//	if (PluginManagerObject)
//	{
//		PluginManagerObject->BeatStartingTime = AudioCursor;
//	}
//
//	CalculateRawBeatArray(BPM, AudioDuration, BeatStartingTime);
//
//	return FReply::Handled();
//}
//
//bool SMyCompoundWidget::ResetAudio()
//{
//	AudioDuration = MySoundWave->Duration;
//	AudioCursor = 0;  //reset audio cursor
//	AudioPercentage = 0;
//	LastPausePercentage = 0.f;
//	MyEditorViewportClient->SetViewLocation(CamaraStartLocation);
//	if (PluginManagerObject)
//	{
//		if (PluginManagerObject->BeatStartingTime)
//		{
//			BeatStartingTime = PluginManagerObject->BeatStartingTime;
//			CalculateRawBeatArray(BPM, AudioDuration, PluginManagerObject->BeatStartingTime);
//		}
//	}
//	else
//	{
//		CalculateRawBeatArray(BPM, AudioDuration);
//	}
//	return true;
//}
//
//void SMyCompoundWidget::InitializeMyCompoundWidget()
//{
//	if (bInitialFlag)
//	{
//		return;
//	}
//	MyEditorViewportClient = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
//	if (MyEditorViewportClient)
//	{
//		World = MyEditorViewportClient->GetWorld();
//		MyEditorViewportClient->SetViewportType(ELevelViewportType::LVT_OrthoXZ);
//		MyEditorViewportClient->SetViewMode(EViewModeIndex::VMI_Lit);
//	}
//	
//	MyIAssetViewport = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor").GetFirstActiveViewport();
//	CamaraStartLocation = MyEditorViewportClient->GetViewLocation();
//	CamaraStartLocation.X = 0;
//
//	
//	
//	SMyCompoundWidget::UpperBorderSize();
//	SMyCompoundWidget::ReloadWave();
//
//	MySecondPluginTextRW = NewObject<UMySecondPluginTextRW>();
//
//}
//
//FReply SMyCompoundWidget::ReloadWave()
//{
//	TArray<AActor*> foundManager;
//	UGameplayStatics::GetAllActorsOfClass(World, AMySecondPluginManager::StaticClass(), foundManager);
//
//
//	if (foundManager.Num() == 1)
//	{
//		PluginManagerObject = Cast<AMySecondPluginManager>(foundManager[0]);
//		if (PluginManagerObject)
//		{
//			//PluginManagerObject->PluginAudioPlayer->SetSound(PluginManagerObject->GameAudio);
//			MyAudioPlayer = PluginManagerObject->PluginAudioPlayer;
//
//			MyAudioPlayer->SetUISound(true);
//			MyAudioPlayer->Activate();
//			bIsManagerValid = true;
//			MyAudioPlayer->SetPaused(true);
//			MySoundWave = (USoundWave*)MyAudioPlayer->Sound;
//
//			MyAudioPlayer->OnAudioPlaybackPercentNative.AddSP(this, &SMyCompoundWidget::HandleOnAudioPlaybackPercentNative);
//
//			LastPausePercentage = 0.f;
//
//
//			if (!MySoundWave)
//			{
//				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Sound Not Set"));
//				bIsManagerValid = false;
//				return FReply::Handled();
//			}
//			MyEditorViewportClient->SetViewLocation(CamaraStartLocation);
//			ResetAudio();
//			DataRawArray = SMyCompoundWidget::WaveToRawDataArray(MySoundWave); //load raw data to AudioWaveformDataArray
//			SMyCompoundWidget::RawDataArrayToRawDrawArray(DataRawArray, ZoomFactor);
//			PlayerRunningSpeed = PluginManagerObject->RunningSpeed;
//			WindowLength = (NUMBER_OF_LINES_IN_WINDOW * ZoomFactor) / ((float)DataRawArray.Num()) * (float)MySoundWave->Duration;
//			BorderUnitPerSecond = (float)BorderWidth /WindowLength ;
//			UE_LOG(LogTemp, Warning, TEXT("Duration: %2.3f."), MySoundWave->Duration);
//			UE_LOG(LogTemp, Warning, TEXT("Data size: %d."), MySoundWave->RawData.GetElementCount());
//			UE_LOG(LogTemp, Warning, TEXT("WindowLength: %f."), WindowLength);
//
//			
//		}
//	}
//	else
//	{
//		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Manager Number Wrong"));
//		bIsManagerValid = false;
//	}
//
//	return FReply::Handled();
//}
//
//FReply SMyCompoundWidget::Reset()
//{
//	ResetAudio();
//	return FReply::Handled();
//}
//
///**
// * Sets border position. Called when constructed. Updates @Borderbox
// *
// */
//void SMyCompoundWidget::UpperBorderSize() 
//{
//
//	FVector2D InViewportSize;
//	BoarderBox.Empty();
//	
//	if (MyIAssetViewport.IsValid())
//	{
//		InViewportSize = FVector2D(MyIAssetViewport->GetActiveViewport()->GetSizeXY());
//	}
//	else InViewportSize = FVector2D(0, 0);
//	
//	float ScaleFactor = 0.3;
//	Padding = 50;
//	BorderWidth = InViewportSize.X - 2 * Padding;
//	BorderHeight = InViewportSize.Y * ScaleFactor;
//	
//	BorderUpperLeft = FVector2D (Padding, Padding);
//	BorderUpperRight = BorderUpperLeft + FVector2D(BorderWidth, 0);
//	BorderLowerRight = BorderUpperRight + FVector2D(0, BorderHeight);
//	BorderLowerLeft = BorderUpperLeft + FVector2D (0, BorderHeight);
//
//	// Inner Box
//	
//	
//
//	BoarderBox.Add(BorderUpperLeft);
//	BoarderBox.Add(BorderUpperRight);
//	BoarderBox.Add(BorderLowerRight);
//	BoarderBox.Add(BorderLowerLeft);
//	BoarderBox.Add(BorderUpperLeft);
//
//	
//}
//
//void SMyCompoundWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) // called everyframe and used for our gamelogic
//{
//	if (!bIsManagerValid)
//	{
//		return;
//	}
//	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
//	UpperBorderSize();
//	UpdateSnapLine();
//
//	if ((!MyAudioPlayer->bIsPaused) && (AudioPercentage <= 1))
//	{
//		//AudioCursor += InDeltaTime * (float)PlaybackSpeed;
//	}
//	else
//	{
//		AudioCursor = (MyEditorViewportClient->GetViewLocation().X - CamaraStartLocation.X) / PluginManagerObject->RunningSpeed;
//		AudioPercentage = AudioCursor / AudioDuration;
//
//	}
//
//
//	SnapLineCursor = (AudioPercentage * DataRawArray.Num()) / ZoomFactor;
//
//	UpdateCamaraLookAt();
//	GetBeatGrid(AudioCursor);
//	//FActiveSound* ActiveSound = MyAudioPlayer->GetAudioDevice()->FindActiveSound(MyAudioPlayer->GetAudioComponentID());
//	//UE_LOG(LogTemp, Warning, TEXT("Playback sound: %s"), *FString::SanitizeFloat( ActiveSound->PlaybackTime));
//
//}
//
//void SMyCompoundWidget::UpdateCamaraLookAt()
//{
//	if (MyEditorViewportClient)
//	{
//		CamaraLocation = MyEditorViewportClient->GetViewLocation();
//		
//		float Delta = AudioCursor * PlayerRunningSpeed;
//
//		SMyCompoundWidget::RawDrawArrayToDrawArray(SnapLineCursor, NUMBER_OF_LINES_IN_WINDOW + SnapLineCursor, DataDrawArray);
//
//		MyEditorViewportClient->SetViewLocation(FVector(CamaraStartLocation.X + Delta, CamaraLocation.Y, CamaraLocation.Z));
//	}
//}
//
//FReply SMyCompoundWidget::OnMouseMove(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
//{
//	SWidget::OnMouseMove(MyGeometry, MouseEvent);
//	return FReply::Unhandled();
//}
//
//void SMyCompoundWidget::UpdateSnapLine()
//{
//	SnapLine[0] = (BorderUpperLeft + BorderUpperRight) / 2;
//	SnapLine[1] = SnapLine[0] + FVector2D(0,3000);		
//}
//
//int32 SMyCompoundWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements,	int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
//{
//		FSlateDrawElement::MakeLines(OutDrawElements,    //render border 
//			LayerId,
//			AllottedGeometry.ToPaintGeometry(),
//			BoarderBox,
//			ESlateDrawEffect::None, 
//			FLinearColor::White,
//			true, 
//			1.f
//		);
//
//
//		FSlateDrawElement::MakeLines(OutDrawElements,    //render snapline 
//			LayerId,
//			AllottedGeometry.ToPaintGeometry(),
//			SnapLine,
//			ESlateDrawEffect::None,
//			FLinearColor::Red,
//			true,
//			2.f
//		);
//
//
//
//		FSlateDrawElement::MakeLines(OutDrawElements,   //render waveform
//			LayerId,
//			AllottedGeometry.ToPaintGeometry(),
//			DrawArray,
//			ESlateDrawEffect::None,
//			FLinearColor::Yellow,
//			true,
//			0.5f
//		);
//
//		//SnapLineCursor
//		SMyCompoundWidget::DrawBeatGrid(AudioCursor, AllottedGeometry, OutDrawElements, LayerId);
//
//
//	return   SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
//}
//
//FReply SMyCompoundWidget::MyPauseAndPlay()
//{
//	if (MyAudioPlayer->bIsPaused)
//	{
//		MyAudioPlayer->Play(AudioCursor);
//		MyAudioPlayer->SetPaused(!MyAudioPlayer->bIsPaused);
//	}
//	else
//	{
//		MyAudioPlayer->SetPaused(!MyAudioPlayer->bIsPaused);
//	}
//
//	return FReply::Handled();
//}
//
//FReply SMyCompoundWidget::MarkTimeStamp()
//{
//	AMySecondPluginTimestamp* newTimeStamp = World->SpawnActor<AMySecondPluginTimestamp>(FVector(MyEditorViewportClient->GetViewLocation().X, 0, MyEditorViewportClient->GetViewLocation().Z), FRotator::ZeroRotator);
//
//	FPlatformerEvent NewEvent;
//	NewEvent.EventUniqueID = newTimeStamp->GetUniqueID();
//	NewEvent.EventTime = AudioCursor;
//
//
//	MySecondPluginTextRW-> AddEvent(NewEvent);
//	
//
//	return FReply::Handled();
//}
//
//void SMyCompoundWidget::ChangePlaybackRate(const float& InFloat)
//{
//	//if (PlaybackSpeed == 1)
//	//{
//	//	PlaybackSpeed = 0.5f;
//	//}
//	//else
//	//{
//	//	PlaybackSpeed = 1.f;
//	//}
//
//	PlaybackSpeed = InFloat;
//
//	MyAudioPlayer->SetPitchMultiplier(PlaybackSpeed);
//
//
//
//	return;
//}
//
//FReply SMyCompoundWidget::TestFunction()
//{
//	UE_LOG(LogTemp, Warning, TEXT("SCompoundWidget TestFunction!!!!"));
//
//	
//
//	return FReply::Handled();
//}
//
//void SMyCompoundWidget::HandleOnAudioPlaybackPercentNative(const class UAudioComponent* AudioComponent, const class USoundWave* PlayingSoundWave, const float PlaybackPercent)
//{
//	if (!MyAudioPlayer->bIsPaused)
//	{
//		AudioPercentage = PlaybackPercent + LastPausePercentage;
//		AudioCursor = AudioPercentage * AudioDuration;
//	}
//	else
//	{
//		LastPausePercentage = AudioPercentage;
//	}
//	//float PlaybackTime = AudioPercentage * AudioDuration;
//	//float PlayerLocation = PlaybackTime * (float)PlayerRunningSpeed;
//	//UE_LOG(LogTemp, Warning, TEXT("Percent: %s, PlaybackTime: %s, PlayerLocation: %s"), *FString::SanitizeFloat(AudioPercentage), *FString::SanitizeFloat(PlaybackTime), *FString::SanitizeFloat(PlayerLocation));
//
//}
//
//FReply SMyCompoundWidget::LoadLevel()
//{
//	FString outString;
//	MySecondPluginTextRW->LoadLevelInfo(TEXT("test.txt"), outString);
//	return FReply::Handled();
//}
//
//FReply SMyCompoundWidget::SaveLevel()
//{
//	MySecondPluginTextRW->SaveLevelInfo("test.txt");
//	return FReply::Handled();
//}
//
//FReply SMyCompoundWidget::RefreshRunningSpeed()
//{
//	//UE_LOG(LogTemp, Warning, TEXT("Running Speed: %s. "), *FString::SanitizeFloat(PluginManagerObject->RunningSpeed));
//	
//	//UE_LOG(LogTemp, Warning, TEXT("Running Speed: %d. "), MySecondPluginTextRW->EventMemo.Num());
//
//	TSubclassOf<AMySecondPluginTimestamp> classToFind;
//	classToFind = AMySecondPluginTimestamp::StaticClass();
//	TArray<AActor*> FoundMarkers;
//	UGameplayStatics::GetAllActorsOfClass(World, classToFind, FoundMarkers);
//
//
//	//for (FPlatformerEvent Event : MySecondPluginTextRW->EventMemo)
//	//{
//	//	FActorSpawnParameters SpawnParms;
//	//	SpawnParms.Name = FName(*Event.EventName);
//	//	FVector SpawnLocation = FVector(Event.EventTime * PluginManagerObject->RunningSpeed, 0, MyEditorViewportClient->GetViewLocation().Z);
//
//
//	//	bool bIsActorFound = false;
//	//	for (AActor* SingleActor : FoundMarkers)
//	//	{
//	//		if (SingleActor->GetName() == Event.EventName)
//	//		{
//	//			SingleActor->SetActorLocation(SpawnLocation);
//	//			bIsActorFound = true;
//	//			break;
//	//		}
//	//	}
//	//	if (!bIsActorFound)
//	//	{
//	//		AMySecondPluginTimestamp* newTimeStamp = World->
//	//			SpawnActor<AMySecondPluginTimestamp>(SpawnLocation, FRotator::ZeroRotator, SpawnParms);
//	//	}
//	//}
//
//
//	
//	return FReply::Handled();
//}
//
//FReply SMyCompoundWidget::SetStartingPosition() 
//{
//	CamaraStartLocation = MyEditorViewportClient->GetViewLocation();
//	return FReply::Handled();
//}
//
//void SMyCompoundWidget::MyHover()
//{
//	//ButtonLabel->SetText(FString(TEXT("Hovered!")));
//}
//
//USoundWave * SMyCompoundWidget::AudiofileLoader(int Selection)  //load wave to *usoundwave
//{
//	
//	FString dir = FPaths::ProjectDir();
//	dir = dir + "Content/AudioFile";
//	
//	UE_LOG(LogTemp, Warning, TEXT("Directory exists? %s."), FPaths::DirectoryExists(dir)? "T" : "F");
//
//	dir = dir + "/1.wav";
//	UE_LOG(LogTemp, Warning, TEXT("File dir: %s. Exist: %s. "), *dir, FPaths::FileExists(dir)? "T" : "F");
//
//	USoundWave* swRef;
//
//
//	UObject* objFinder = nullptr;
//
//	if (Selection == 1)
//	{
//		objFinder = StaticLoadObject(USoundWave::StaticClass(), nullptr, TEXT("SoundWave'/Game/AudioFile/1.1'"), *dir);
//	}
//
//	else 
//	{
//		objFinder = StaticLoadObject(USoundWave::StaticClass(), nullptr, TEXT("SoundWave'/Game/AudioFile/2.2'"), *dir);
//	}
//
//	swRef = dynamic_cast <USoundWave*> (objFinder);
//			
//
//	return swRef;
//}
//
//void SMyCompoundWidget::CheckWaveformData(uint8 * InputArray)
//{
//	for (int i = 0; i < MySoundWave->RawPCMDataSize; i++)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Duration: %d."), MySoundWave->RawPCMDataSize);
//	}
//	
//	TArray<TArray<float>> OutAmplitudes;
//
//	DataRawArray = SMyCompoundWidget::WaveToRawDataArray(MySoundWave);
//
//	UE_LOG(LogTemp, Warning, TEXT("USoundWaveCount: %d."), MySoundWave->RawData.GetElementCount());
//	UE_LOG(LogTemp, Warning, TEXT("OutAmplitudesCount: %d."), DataRawArray.Num());
//
//
//	
//}
//
///**
// Extract data from USoundWave and put them into RawDataArray
// @param Soundwave, the Soundwave pointer
// @return TArray containing raw data from the USoundWave object. 
//*/
//TArray<float> SMyCompoundWidget::WaveToRawDataArray(USoundWave * SoundWave)
//{
//	TArray<float> Output;
//	const int32 NumChannels = SoundWave->NumChannels;
//
//	if ((NumChannels == 0) || (SoundWave->RawData.GetBulkDataSize() == 0))
//	{
//		return Output;
//	}
//
//	uint8* RawWaveData = (uint8*)SoundWave->RawData.Lock(LOCK_READ_ONLY);
//	int32 RawDataSize = SoundWave->RawData.GetBulkDataSize();
//	FWaveModInfo WaveInfo;
//	
//	if (WaveInfo.ReadWaveHeader(RawWaveData, RawDataSize, 0))
//	{
//		uint32 SampleCount = WaveInfo.SampleDataSize / (2 * NumChannels);
//
//		const int16* SamplePtr = reinterpret_cast<const int16*>(WaveInfo.SampleDataStart);
//		
//		for (uint32 SampleIndex = 0; SampleIndex < SampleCount; ++SampleIndex)   
//		{
//			int64 SampleSum = 0;
//			for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)  
//			{
//				SampleSum += (*SamplePtr);
//				SamplePtr++;
//			}
//			SampleSum = SampleSum / (float)NumChannels;
//			Output.Add(SampleSum);
//		}
//	}
//
//	SoundWave->RawData.Unlock();
//
//	return Output;
//}
//
///*
// Extract raw data from RawDataArray and put them into RawDrawArray
// @param InputArray, the RawDataArray from USoundWave
// @param BucketSize, we only push the absolute max value in the bucket into the DrawArray.
// Therefore, by default, the size of RawDrawArray is (InputArray.size()/200)
//*/
//void SMyCompoundWidget::RawDataArrayToRawDrawArray(const TArray<float>& InputArray, int BucketSize )
//{
//	DataDrawArray.Empty();
//	float YOffset = Padding + BorderHeight / 2.f;
//	int InputArrayIndex = 0;
//	int NumberOfBuckets = (InputArray.Num() - (InputArray.Num() % BucketSize)) / BucketSize;
//	float AbsMax = InputArray[0];
//	for (int i = 0; i < InputArray.Num(); i++)
//	{
//		if (FMath::Abs(InputArray[i]) > AbsMax)
//		{
//			AbsMax = InputArray[i];
//		}
//	}
//	float YScale = BorderHeight / (2 * AbsMax);
//	for (int i = 0; i < NumberOfBuckets; i++)
//	{
//		float Temp = 0;
//
//		for (int j = 0; j < BucketSize; j++)      //absmax with bucket
//		{
//			if (FMath::Abs(InputArray[InputArrayIndex]) > Temp)
//			{
//				Temp = InputArray[InputArrayIndex];
//			}
//			InputArrayIndex++;
//		}
//
//
//		Temp = YOffset - (Temp * YScale);
//
//		DataDrawArray.Add(Temp);
//
//	}
//
//
//}
//
///**
// Extract raw data from RawDataArray and put them into TArray<float> for drawing
// @param InputArray, the RawDataArray from USoundWave
// @param SampleCount, how many samples to draw. For example, If InputArray contains 20K samples, 
// putting 10k at this para will only draw half of the waveform of the file
// @param BucketSize, we only push the absolute max value in the bucket into the DrawArray. 
// Therefore, by default, the size of DrawArray is (InputArray.size()/200)
//*/
//void SMyCompoundWidget::RawDrawArrayToDrawArray(int Start, const int End, TArray<float>& InArrayToBeDrew)
//{
//	//get # of steps
//	//take the peak value of each bucket
//	//add to array
//	/*
//	This function serves as a moving window of deciding what's shown on the screen, picking the "window" section out of RawDrawArray
//	if (header-start)<0 -> window is larger than default 
//	if (header-start)>0  &&  if (end+tail)<InArray.num() -> still going
//
//	if (end+tail)>InArray.num() -> fill default
//
//	//Todo: is it possible to change the pointer to the array instead of rewritting the array every frame? 
//
//	*/
//
//
//
//	DrawArray.Empty();
//	int ArrayIndex = Start;										 //starting point of the InArray
//	int Steps = 1;												//how many steps has been taken. This process always take NUMBER_OF_LINES_IN_WINDOW steps
//	int NumberOfSteps = NUMBER_OF_LINES_IN_WINDOW;		
//	float YOffset = Padding + BorderHeight / 2.f;				//default Y position, horizontal line
//	float XCord = Padding;										//X  starting cord   //Todo, just change Y, leave X
//	float XIncrement = (float)BorderWidth / NumberOfSteps;		
//	int Header = NUMBER_OF_LINES_IN_WINDOW/2;
//	int Tail = NUMBER_OF_LINES_IN_WINDOW/2;
//	
//	EDrawType NextDrawType = EDrawType::Header;
//	
//	int HeadNeeded = Header - Start;
//	if (HeadNeeded >= 0)
//	{
//		ArrayIndex = 0;
//	}
//	else
//	{
//		NextDrawType = EDrawType::Data;
//		ArrayIndex = ArrayIndex - NumberOfSteps/2;
//		if (ArrayIndex < 0) ArrayIndex = 0;
//	}
//
//
//
//	while (Steps < NumberOfSteps)
//	{
//		float YTemp = YOffset;
//		switch (NextDrawType)
//		{
//			case EDrawType::Data:
//			{
//				/*
//				if array index in range, fill
//				else mark next as footer and break;
//				*/
//
//				if (ArrayIndex > InArrayToBeDrew.Num() - 1)
//				{
//					NextDrawType = EDrawType::Footer;
//					break;
//				}
//
//				YTemp = InArrayToBeDrew[ArrayIndex];
//				ArrayIndex++;
//				break;
//			}
//			case EDrawType::Header:
//			{
//				/*
//				if (headneeded<0), break, nexttype = data
//				else fill head, headneede--;
//				*/
//				if (HeadNeeded <= 0)
//				{
//					NextDrawType = EDrawType::Data;
//					break;
//				}
//				else
//				{
//					HeadNeeded--;
//				}
//				break;
//			}
//			case EDrawType::Footer:
//			{
//				/*
//				fill tail, the while take cares of ending condition
//				*/
//				break;
//			}
//		}
//		DrawArray.Add(FVector2D(XCord, YTemp));
//		XCord += XIncrement;
//		Steps++;
//	}
//}
//
///*
//calculatess beat array. e.g. if bpm = 60. BeatRawArray = {0,1,2,3 ...}
//*/
//void SMyCompoundWidget::CalculateRawBeatArray(const float& InBPM, const float& InAudioDuation, const float& InBeatStartingTime)
//{
//	BeatRawArray.Empty();
//
//	BeatRawArray.Add(0.f);
//
//	float NextBeatTime = 0.f + InBeatStartingTime;
//
//	float BeatInveral = 60.f / InBPM;
//
//	while (NextBeatTime <= InAudioDuation)
//	{
//		BeatRawArray.Add(NextBeatTime);
//		NextBeatTime += BeatInveral;
//	}
//	return;
//
//}
//
///*given a point, it calculates the beat grid in that window.
//For example, if there's beat at 3s and the window is 5s, it calculates those beats.
//Called every frames. */
//void SMyCompoundWidget::GetBeatGrid(float CurrentCursor)
//{
//	float  Border = 0;
//
//	int32 StartingIndex = 1;
//	int32 LastXCord = Padding;
//	float LowerBound = CurrentCursor - WindowLength / 2; //where beat grid starts to render. -> left side of the screen. 
//	if (CurrentCursor - WindowLength / 2 < WindowLength / 2)  //if cursor is less than half of window length, that means window is fill with head. No beat should be rendered.
//	{
//		//	return;
//	}
//
//	BeatDrawArray.Empty();
//
//	if (CurrentCursor < WindowLength / 2) //header presented
//	{
//		Border = CurrentCursor + WindowLength / 2;
//		LastXCord = LastXCord + (WindowLength / 2 - CurrentCursor) * BorderUnitPerSecond;
//		//TODO add first beat
//	}
//	else if (CurrentCursor > AudioDuration)  //cursor is beyond audio file
//	{
//		return;
//	}
//	else                                        //default
//	{
//		Border = CurrentCursor + WindowLength / 2;
//		while ((BeatRawArray[StartingIndex] < (LowerBound)) && (StartingIndex < BeatRawArray.Num()))
//		{
//			StartingIndex++;
//		}
//
//		LastXCord = LastXCord + (BeatRawArray[StartingIndex - 1] - (LowerBound)) * BorderUnitPerSecond;
//	}
//
//	while ((BeatRawArray[StartingIndex] < Border) && (StartingIndex < BeatRawArray.Num()))
//	{
//
//		float XCord = LastXCord + (BeatRawArray[StartingIndex] - BeatRawArray[StartingIndex - 1]) * BorderUnitPerSecond;
//
//		
//		BeatDrawArray.Add(FVector2D(XCord, Padding));   //top point
//		BeatDrawArray.Add(FVector2D(XCord, Padding) + FVector2D(0, 500)); //bottom point
//
//		StartingIndex++;
//
//		LastXCord = XCord;
//
//	}
//}
//
///*
//this function is called multiple times while on painting phase. 
//e.g., if theres 2 beat line in presence, BeatDrawArray will have 4 points [1top, 1bot, 2top, 2bot]
//this function groups 1top and 1bot as the first line, 2top and 2 bot as the second line. 
//*/
//void SMyCompoundWidget::DrawBeatGrid(float CurrentCursor, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const //CurrentCorsor feeds audiocursor
//{
//
//	for (int32 i = 0; i < BeatDrawArray.Num(); i += 2)
//	{
//		FSlateDrawElement::MakeLines(OutDrawElements,    //render beat grid one by one
//			LayerId,
//			AllottedGeometry.ToPaintGeometry(),
//			{ BeatDrawArray[i], BeatDrawArray[i+1] },
//			ESlateDrawEffect::None,
//			FLinearColor::Green,
//			true,
//			0.5
//		);
//	}
//	
//}
//
//FReply SMyCompoundWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "onkeydown");
//	//SnapToBeat();
//	return FReply::Handled();
//}
//
////need to revise
//void SMyCompoundWidget::SnapToBeat()
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "SnapToBeat");
//
//	//UE_LOG(LogTemp, Warning, TEXT("%i"), MyEditorViewportClient->current);
//	
//	//leftmost, rightmost
//
//
//	/*
//	2 case: on beat and not on beat
//	if on beat, left most & right most = current index +- 1
//	if not on beat, find left and right index 
//
//	check if mouseX < first beat, if so, leftmost index = self, rightmost index = [0]
//	check if mouseX > last beat, if so, leftmost index = index[length], rightmost index = self
//
//	check if (mouseX - drawbeatarray[i]) * (mouseX - drawbeatarray[i+1]) < 0
//	if so, mouseX fall in range, leftmost = i, rightmost = i+1;
//	if == 0, mouseX fall ON BEAT, leftmost = i-1, rightmost = i+1;
//	else, keel moving on
//	*/
//
//	FVector2D ViewPortSize = FVector2D(MyEditorViewportClient->Viewport->GetSizeXY());
//
//	if (MyEditorViewportClient->Viewport)
//	{
//		int32 MouseDeltaX = MyEditorViewportClient->GetCachedMouseX() - MyEditorViewportClient->Viewport->GetMouseX();
//		/* delta < 0 -> mouse moves to the right */
//		/* delta > 0 -> mouse moves to the left*/
//		int32 NewBeatIndex = -1;
//		int32 LeftMostIndex = -1;
//		int32 RightMostIndex = -1;
//
//		int32 CurrentMouseX = MyEditorViewportClient->Viewport->GetMouseX();
//		
//		if (CurrentMouseX <= BeatDrawArray[0].X)
//		{
//			LeftMostIndex = 0;
//			RightMostIndex = 0;
//		}
//		else if (CurrentMouseX >= BeatDrawArray[BeatDrawArray.Num()-1].X)
//		{
//			LeftMostIndex = BeatDrawArray.Num();
//			RightMostIndex = BeatDrawArray.Num();
//		}
//
//		else
//		{
//			for (int32 BeatArrayIndex = 0; BeatArrayIndex <= BeatDrawArray.Num() - 2; BeatArrayIndex++)   //check if mouse is on beat already
//			{
//				int32 LeftBeat = BeatDrawArray[BeatArrayIndex].X;
//				int32 RightBeat = BeatDrawArray[BeatArrayIndex + 1].X;
//
//				int32 Direction = (CurrentMouseX - LeftBeat) * (CurrentMouseX - RightBeat); //<0 in range, >0 out of range, ==0, on beat
//				if (Direction == 0)
//				{
//					LeftMostIndex = BeatArrayIndex-1;
//					RightMostIndex = BeatArrayIndex+1;
//				}
//				else if (Direction < 0)
//				{
//					LeftMostIndex = BeatArrayIndex;
//					RightMostIndex = BeatArrayIndex + 1;
//				}
//			}
//		}
//
//		if (MouseDeltaX > 5)   //set to left
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Set to Left, %i"), MouseDeltaX);
//			if (LeftMostIndex > 0 && LeftMostIndex < BeatDrawArray.Num())
//			{
//				MyEditorViewportClient->Viewport->SetMouse(BeatDrawArray[LeftMostIndex].X, ViewPortSize.Y / 2);
//			}
//		}
//		else if (MouseDeltaX < -5)  //set to right
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Set to Right, %i"), MouseDeltaX);
//			if (RightMostIndex > 0 && RightMostIndex < BeatDrawArray.Num())
//			{
//				MyEditorViewportClient->Viewport->SetMouse(BeatDrawArray[RightMostIndex].X, ViewPortSize.Y / 2);
//			}
//		}
//
//	}
//
//}
//
//
//END_SLATE_FUNCTION_BUILD_OPTIMIZATION
//#if PLATFORM_WINDOWS
//#pragma optimize("", on)
//#endif
