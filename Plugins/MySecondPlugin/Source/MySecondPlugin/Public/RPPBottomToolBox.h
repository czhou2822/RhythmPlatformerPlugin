// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"


/**
 * 
 */
class MYSECONDPLUGIN_API SRPPBottomToolBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPBottomToolBox)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

public:
	TSharedPtr<SSlider> PlaybackSlider;

public:
	
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic



};
