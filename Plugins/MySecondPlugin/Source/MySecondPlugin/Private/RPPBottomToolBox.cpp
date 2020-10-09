// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Layout/SConstraintCanvas.h"


#include "RPPBottomToolBox.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPBottomToolBox::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::Visible);

	ChildSlot
	[
		SNew(SConstraintCanvas)
		+SConstraintCanvas::Slot()
		.Anchors(FAnchors(0.0f, 0.0f))
		.Alignment(FVector2D(0.0, 0.0))
		.AutoSize(true)
		[
			SNew(SBox)
			.WidthOverride(350)
			.HeightOverride(30)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Playback Speed: 1X")))
				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillWidth(1.0)
				[
					SNew(SBox)
					[
						SAssignNew(PlaybackSlider, SSlider)
					]

				]
			]
		]

		+SConstraintCanvas::Slot()
		.Anchors(FAnchors(0.5f,0.5f))
		.Alignment(FVector2D(0.5,0.5))
		.AutoSize(true)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Text(FText::FromString(TEXT("Play/Pause")))
		]
	];
	

}

void SRPPBottomToolBox::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
