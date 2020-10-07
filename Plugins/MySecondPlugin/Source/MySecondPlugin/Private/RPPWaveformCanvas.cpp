// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPWaveformCanvas.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPWaveformCanvas::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(300)
			.HeightOverride(400)
			[
				SNew(SImage)
				.RenderOpacity(1.f)
			]
		];
}

void SRPPWaveformCanvas::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
