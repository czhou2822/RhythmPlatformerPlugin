//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "SlateBasics.h"
//#include "Sound/SoundWave.h"
//#include "ILevelViewport.h"
//#include "Components/AudioComponent.h"
//#include "DrawElements.h"
//#include "Widgets/SCompoundWidget.h"
//#include "Kismet/GameplayStatics.h"
//#include "GenericPlatform/GenericPlatformMath.h"
//#include "MySecondPluginTextRW.h"
//#include "EditorViewportClient.h"
//
//#include "RPPUtility.h"
//
//
//
//class JsonObject;
//class AMySecondPluginManager;
//class UMySecondPluginTextRW;
//
//
///**
// * 
// */
//class MYSECONDPLUGIN_API SMyCompoundWidget : public SCompoundWidget
//{
//public:
//	SLATE_BEGIN_ARGS(SMyCompoundWidget)
//		:_Label(TEXT("Default Value"))
//	//	,_ButtonClicked()
//	{}
//	SLATE_ATTRIBUTE(FString, Label)
//	//	SLATE_EVENT(FOnClicked, ButtonClicked)
//	SLATE_END_ARGS()
//
//	/** Constructs this widget with InArgs */
//private:
//	UWorld* World;
//	TArray<FVector2D> BoarderBox;
//
//	TArray<FVector2D> SnapLine;
//
//	TArray<FVector2D> DrawArray;	//DrawArray
//
//
//	TArray<float> DataRawArray;    //Raw data from wave file   
//
//	TArray<float> DataDrawArray;   //RawDrawArray processed from RawDataArray, contain (RawDataArray.size()/bucketsize) elements
//
//	TArray<FVector2D> BeatDrawArray;	//BeatArray
//
//	TArray<float> BeatRawArray = { 0.f, 1.f, 2.f, 3.f, 4.f,5.f, 6.f };    //Raw beat info; elements in second. for example, if BPM = 60, it shoud be [0,1,2,3,4,5...]
//
//	
//
//	const int32 NUMBER_OF_LINES_IN_WINDOW = 20000;
//
//	float WindowLength = 0.f;// how much time is window represented. For example, if #_LINES_IN_WINDOW = 20k, this para represents how long this 20k is in second. 
//							 // it is calculated by NUMBER_OF_LINES_IN_WINDOW * ZoomFactor. This gives how much samples in the window
//							 // it then divided by total of samples. multiply this ratio by audio duration gives WindowLength in total. 
//	int32 ZoomFactor = 5;      //how many samples in each bucket, for example, if this is 32, RawDrawArray takes ONE peak value out of 32 in RawDataArray
//	
//	FVector2D BorderUpperLeft;
//	FVector2D BorderUpperRight ;
//	FVector2D BorderLowerRight;
//	FVector2D BorderLowerLeft;
//
//	FVector CamaraStartLocation;
//	FVector CamaraLocation;
//
//	FEditorViewportClient* MyEditorViewportClient;
//	USoundWave* MySoundWave;
//	UAudioComponent* MyAudioPlayer;
//	float AudioCursor = 0; //how long has the audio been played
//	float CameraCursor = 0; //where is camara lookat, usually audiocursor * player running speed
//	int32 SnapLineCursor = 0;
//	float AudioPercentage = 0;
//	float AudioDuration = 0;
//	float BPM = 78.f;  //78
//	float BorderUnitPerSecond = 0.f;  //how much BorderUnit is ONE second represented. E.g, if Para = 50, it means 50 BorderUnits is ONE second. 
//	float BeatStartingTime = 0.f;
//	
//
//	bool bInitialFlag = false;
//	bool bIsManagerValid = false;
//	bool bIsWidgetPause = false;
//	bool bShowBeatGrid = false;
//	bool bShowSubBeats = false;
//
//	TSharedPtr<IAssetViewport> MyIAssetViewport;
//	int32 Padding;
//	int32 BorderWidth;
//	int32 BorderHeight;
//	float PlayerRunningSpeed;
//	float PlaybackSpeed;
//	float LastPausePercentage;
//
//    UMySecondPluginTextRW* MySecondPluginTextRW;
//	AMySecondPluginManager* PluginManagerObject;
//
//public:
//
//private:
//	
//	void UpdateCamaraLookAt();
//
//	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic
//
//	FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
//
//	void RawDataArrayToRawDrawArray(const TArray<float>& InputArray, int BucketSize);
//
//	void RawDrawArrayToDrawArray(const int Start, const int End, TArray<float>& InRawDrawArray);
//
//	//calculates BeatDrawArray
//	void GetBeatGrid(float CurrentCursor);
//
//	//calls make line using BeatDrawArray
//	void DrawBeatGrid(float CurrentCursor, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;
//
//	void UpdateSnapLine();
//
//	void InitializeMyCompoundWidget();
//
//	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
//
//
//
//	/* Button Events   */
//	FReply MyPauseAndPlay();
//	FReply Reset();
//	FReply ReloadWave();
//	FReply MarkTimeStamp();
//	FReply SetStartingPosition();
//	FReply TestFunction();
//	FReply LoadLevel();
//	FReply SaveLevel();
//	FReply RefreshRunningSpeed();
//	FReply ChangeBeatStartingTime();
//
//
//public:
//	void UpperBorderSize()  ;
//	void Construct(const FArguments& InArgs);
//	TAttribute<FString> Label;
//	TSharedPtr<STextBlock> ButtonLabel;
//	
//	virtual int32 OnPaint(const FPaintArgs& Args, 
//						const FGeometry& AllottedGeometry, 
//						const FSlateRect& MyClippingRect, 
//						FSlateWindowElementList& OutDrawElements, 
//						int32 LayerId, 
//						const FWidgetStyle& InWidgetStyle, 
//						bool bParentEnabled) const override;
//
//
//	void MyHover();
//
//	USoundWave* AudiofileLoader(int Selection);
//	
//	void CheckWaveformData(uint8* InputArray);
//
//	TArray<float> WaveToRawDataArray(USoundWave* SoundWave);
//
//	//UFUNCTION()
//	void HandleOnAudioPlaybackPercentNative(const class UAudioComponent* AudioComponent, const class USoundWave* PlayingSoundWave, const float PlaybackPercent);
//	
//	UFUNCTION()
//	void HandleOnSliderChanged(float InFloat);
//
//
//
//	/*
//	generates elements for RawBeatArray
//	e.g., if bpm = 60, RawBeatArray = {0,1,2,3}
//	*/
//	void CalculateRawBeatArray(const float& InBPM, const float& InAudioDuation, const float& InBeatStartingTime = 0.0f);
//
//	bool ResetAudio();
//
//	void SnapToBeat();
//
//	void ChangePlaybackRate(const float& InFloat);
//
//};
