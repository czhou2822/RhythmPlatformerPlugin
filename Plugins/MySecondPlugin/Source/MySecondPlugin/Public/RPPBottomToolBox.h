// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//engine includes
#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

//user includes
#include "RPPMain.h"



/**
 * 
 */
class MYSECONDPLUGIN_API SRPPBottomToolBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPBottomToolBox)
	{}
	SLATE_ARGUMENT(int32, TestValue)
	SLATE_ARGUMENT(class SRPPMain*, RhythmPlatformingPluginMain)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */


private:

	//TAttribute< int32 > TestValue;

	int32 NewValue;

	SRPPMain* RPPMain;

	TSharedPtr<STextBlock> PlaybackRateText;

	TSharedPtr<SSlider> PlaybackSlider;

public:
	
	void Construct(const FArguments& InArgs);

	FReply TogglePlay();

	void HandleOnSliderChanged(float InFloat);

};
