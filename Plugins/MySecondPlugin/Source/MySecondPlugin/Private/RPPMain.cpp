// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPMain.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPMain::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::SelfHitTestInvisible);
	ChildSlot
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			.Padding(FMargin(10.0,50.0,0.0,0.0))
			[
				SAssignNew(RPPButtonVBox, SRPPButtonVBox)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(RPPMainCanvas, SRPPMainCanvas)
			]
		];
}

void SRPPMain::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
