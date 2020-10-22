// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPMainCanvas.h"
#include "RPPUtility.h"




BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SRPPMainCanvas::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::SelfHitTestInvisible);
	RPPMain = InArgs._RhythmPlatformingPluginMain;
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
				.Padding(0.0f,TopPadding,0.0f,0.0f)
				[
					SAssignNew(RPPWaveformCanvas, SRPPWaveformCanvas)
					.Visibility(EVisibility::SelfHitTestInvisible)
					.RhythmPlatformingPluginMain(RPPMain)
				]

				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(RPPBottomToolBox, SRPPBottomToolBox)
					.Visibility(EVisibility::Visible)
					.RhythmPlatformingPluginMain(RPPMain)

				]
			]
		];


}

void SRPPMainCanvas::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SetSnapLine();
}

int32 SRPPMainCanvas::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{


	FSlateDrawElement::MakeLines(OutDrawElements,    //render snapline 
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		SnapLine,
		ESlateDrawEffect::None,
		FLinearColor::Red,
		true,
		2.f
	);


	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

void SRPPMainCanvas::SetSnapLine()
{
	FVector2D ContentSize = GetCachedGeometry().GetAbsoluteSize();


	SnapLine.Empty();
	SnapLine.Add(FVector2D(ContentSize.X / 2 , TopPadding));
	SnapLine.Add(FVector2D(ContentSize.X / 2, ContentSize.Y));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
