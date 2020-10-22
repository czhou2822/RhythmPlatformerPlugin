// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

#include "Widgets/SCompoundWidget.h"


/**
 * 
 */
class MYSECONDPLUGIN_API SRPPWaveformCanvas : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPWaveformCanvas)
	{}
	SLATE_ARGUMENT(class SRPPMain*, RhythmPlatformingPluginMain)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

private:
	TArray<FVector2D> BoarderBox;

	class SRPPMain* RPPMain;


public:

	float BorderWidth = 0.f;

	float BorderHeight = 0.f;


public:
	
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic

	virtual int32 OnPaint(const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyClippingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override;

	//canvas related
	
	//update the white border
	void UpperBorderSize();

	//calculates BeatDrawArray
	void GetBeatGrid(float CurrentCursor);

	//calls make line using BeatDrawArray
	void DrawBeatGrid(float CurrentCursor, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;

};
