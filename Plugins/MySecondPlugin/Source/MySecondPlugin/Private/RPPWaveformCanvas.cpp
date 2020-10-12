// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPWaveformCanvas.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPWaveformCanvas::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(800)
			.HeightOverride(200)
			[
				SNew(SImage)
				.RenderOpacity(0.2f)
			]
		];
}

void SRPPWaveformCanvas::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

	UpperBorderSize();

}

int32 SRPPWaveformCanvas::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

	FSlateDrawElement::MakeLines(OutDrawElements,    //render border 
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		BoarderBox,
		ESlateDrawEffect::None,
		FLinearColor::White,
		true,
		1.f
	);



	return   SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

/**
 * Sets border position. Called when constructed. Updates @Borderbox
 *
 */
void SRPPWaveformCanvas::UpperBorderSize()
{

	FVector2D ContentSize = GetCachedGeometry().GetAbsoluteSize();

	
	

	BoarderBox.Empty();

	float ScaleFactor = 0.3;



	float BorderWidth = ContentSize.X;
	float BorderHeight = ContentSize.Y;

	FVector2D BorderUpperLeft = FVector2D(0, 0);
	FVector2D BorderUpperRight = BorderUpperLeft + FVector2D(BorderWidth, 0);
	FVector2D BorderLowerRight = BorderUpperRight + FVector2D(0, BorderHeight);
	FVector2D BorderLowerLeft = BorderUpperLeft + FVector2D(0, BorderHeight);

	// Inner Box

	

	BoarderBox.Add(BorderUpperLeft);
	BoarderBox.Add(BorderUpperRight);
	BoarderBox.Add(BorderLowerRight);
	BoarderBox.Add(BorderLowerLeft);
	BoarderBox.Add(BorderUpperLeft);


}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
