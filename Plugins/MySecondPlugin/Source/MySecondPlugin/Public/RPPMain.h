// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//engine includes
#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"


//user includes
#include "RPPButtonVBox.h"
#include "RPPMainCanvas.h"


/**
 * 
 */
class MYSECONDPLUGIN_API SRPPMain : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SRPPMain)
	{}
	SLATE_ARGUMENT(float, RPPWidth)
		SLATE_ARGUMENT(float, RPPHeight)
		SLATE_END_ARGS()

		/** Constructs this widget with InArgs */


private:

	bool bIsValidated = false;

	float OrthoZoom = 0.f;

	class URPPUtility* RPPUtil;

	class UAudioComponent* AudioComponent;

	float AudioPercentage = 0.f;

	bool bIsPlaying = false;      //is track playing

	float LastPausePercentage = 0.f;  //played percentage since last paused

	int32 SnaplineCursor = 0; //index of the RawDrawArray. 

	const int32 NUMBER_OF_LINES_IN_WINDOW = 10000; //how many lines in waveform

	int32 ZoomFactor = 5;      //how many samples in each bucket, for example, if this is 32, RawDrawArray takes ONE peak value out of 32 in RawDataArray

	FVector CameraStartingLocation = FVector(0, 0, 0);

	USoundWave* SoundWave = nullptr;


public:
	TSharedPtr<class SRPPButtonVBox> RPPButtonVBox;

	TSharedPtr<class SRPPMainCanvas> RPPMainCanvas;

	class FEditorViewportClient* EditorViewportClient;

//	class AMySecondPluginManager* PluginManagerObject;

	class ARPPPluginManager* RPPPluginManager;


	float AudioCursor = 0.f;    //playtime of the track, in seconds

	float WindowLength = 0.f;	//how many time repersented in width 

	float AudioDuration = 0.f;


private:
	//called every frame
	void UpdateCamaraLookAt();

	void HandleOnAudioPlaybackPercentNative(const class UAudioComponent* AudioComponent, const class USoundWave* PlayingSoundWave, const float PlaybackPercent);


public:

	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic

	//plugin init
	void Initilization();

	//reset viewport, going back to the beginning of the level
	void ResetViewport();

	void TogglePlay();

	void ChangePlaybackSpeed(float InFloat);

	void SetCurrentAsBeatStartingTime();

	//process soundwave in PluginObject->audiocomponent
	void ProcessSoundWave();

	//called when viewport zoomed
	int GetZoomFactor();

	void ProcessZoom();

	void OnEditorCameraMoved(const FVector& InFVector, const FRotator& InRotator, ELevelViewportType InViewportType, int32 InInt);

	void HandleOnNewActorsDropped(const TArray<UObject*>& InUObjects, const TArray<AActor*>& InAActors);

	void HandleOnNewRPPEventPlaced(int32 InRPPID);

	void HandleOnNewRPPEventRemoved(int32 InRPPID);

	bool ValidatePluginManager(ARPPPluginManager* RPPPluginManager);

};
