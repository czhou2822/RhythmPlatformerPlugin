// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPMainCanvas.h"





BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SRPPMainCanvas::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(RPPWaveformCanvas, SRPPWaveformCanvas)

			]

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SAssignNew(RPPBottomToolBox, SRPPBottomToolBox)

			]

		];
}

void SRPPMainCanvas::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
