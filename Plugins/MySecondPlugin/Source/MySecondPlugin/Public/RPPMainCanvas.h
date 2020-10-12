// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//engine includes
#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

//custom includes
#include "RPPBottomToolBox.h"
#include "RPPWaveformCanvas.h"


/**
 * 
 */
class MYSECONDPLUGIN_API SRPPMainCanvas : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPMainCanvas)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

public:

	TSharedPtr<SRPPBottomToolBox> RPPBottomToolBox;

	TSharedPtr<SRPPWaveformCanvas> RPPWaveformCanvas;


public:
	
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic




};
