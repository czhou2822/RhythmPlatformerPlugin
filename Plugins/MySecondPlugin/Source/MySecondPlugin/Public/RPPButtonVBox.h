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
class MYSECONDPLUGIN_API SRPPButtonVBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPButtonVBox)
	{}
	SLATE_ARGUMENT(class SRPPMain*, RhythmPlatformingPluginMain)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */


private:
	class SRPPMain* RPPMain;

private:

	FReply BackToTop();

	FReply ReloadWave();

	//FReply MarkTimeStamp();

	//FReply SetStartingPosition();

	FReply LoadLevel();

	FReply SaveLevel();

	FReply RefreshRunningSpeed();

	FReply ChangeBeatStartingTime();

public:
	void Construct(const FArguments& InArgs);




};
