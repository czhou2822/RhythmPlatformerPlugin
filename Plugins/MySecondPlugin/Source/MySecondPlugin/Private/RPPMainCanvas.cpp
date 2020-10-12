// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPMainCanvas.h"





BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SRPPMainCanvas::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::SelfHitTestInvisible);
	ChildSlot
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SVerticalBox)      //main canvas vbox
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(0.0f,50.f,0.0f,0.0f)
				[
					SAssignNew(RPPWaveformCanvas, SRPPWaveformCanvas)
					.Visibility(EVisibility::SelfHitTestInvisible)
				]

				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(RPPBottomToolBox, SRPPBottomToolBox)
					.Visibility(EVisibility::Visible)

				]

			]


		];
}

void SRPPMainCanvas::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
