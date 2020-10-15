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
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */


private:

	class AMySecondPluginManager* PluginManagerObject;

	class URPPUtility* RPPUtil;

	class FEditorViewportClient* EditorViewportClient;

	class UAudioComponent* AudioComponent;

	float AudioDuration = 0.f;

	float AudioPercentage = 0.f;

	float AudioCursor = 0.f;    //playtime of the track, in seconds

	bool bIsPlaying = false;      //is track playing

	float LastPausePercentage = 0.f;  //played percentage since last paused

	int32 SnaplineCursor = 0; //index of the RawDrawArray. 

	FVector CameraStartingLocation = FVector(0, 0, 0);




public:
	TSharedPtr<class SRPPButtonVBox> RPPButtonVBox;

	TSharedPtr<class SRPPMainCanvas> RPPMainCanvas;


private:
	//called every frame
	void UpdateCamaraLookAt();

	void HandleOnAudioPlaybackPercentNative(const class UAudioComponent* AudioComponent, const class USoundWave* PlayingSoundWave, const float PlaybackPercent);


public:
	
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic

	//plugin init
	void Initilization();

	void ProcessSoundWave(USoundWave* InSoundWave);

	//reset viewport, going back to the beginning of the level
	void ResetViewport();

	void TogglePlay();

	void ChangePlaybackSpeed(float InFloat);



};
