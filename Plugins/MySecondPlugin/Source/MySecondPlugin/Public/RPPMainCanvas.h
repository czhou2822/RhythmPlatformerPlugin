// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//engine includes
#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

//custom includes
#include "RPPBottomToolBox.h"
#include "RPPMain.h"
#include "RPPWaveformCanvas.h"


/**
 * 
 */
class MYSECONDPLUGIN_API SRPPMainCanvas : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPMainCanvas)
	{}
	SLATE_ARGUMENT(class SRPPMain*, RhythmPlatformingPluginMain)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

private:

	//Snapline, just 2 points
	TArray<FVector2D> SnapLine;

	class SRPPMain* RPPMain;

	float TopPadding = 50;

public:

	TSharedPtr<class SRPPBottomToolBox> RPPBottomToolBox;

	TSharedPtr<SRPPWaveformCanvas> RPPWaveformCanvas;


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

	void SetSnapLine();


};
