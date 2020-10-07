// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPBottomToolBox.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPBottomToolBox::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::Visible);

	ChildSlot
	[
		SNew(SCanvas)
		+SCanvas::Slot()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Playback Speed: 1X")))
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillWidth(1.f)
			[
				SNew(SBox)
				
				[
					SAssignNew(PlaybackSlider, SSlider)
				]

			]
		]

		//+SCanvas::Slot()
		//.anchor
		//[
		//	SNew(SButton)
		//	.HAlign(HAlign_Center)
		//	.VAlign(VAlign_Center)
		//	.Text(FText::FromString(TEXT("Play/Pause")))
		//]
	];
	

}

void SRPPBottomToolBox::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
