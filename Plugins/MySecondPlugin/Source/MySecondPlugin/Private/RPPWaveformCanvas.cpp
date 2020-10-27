// Fill out your copyright notice in the Description page of Project Settings.


//engine includes



//user includes
#include "RPPWaveformCanvas.h"
#include "RPPUtility.h"
#include "RPPMain.h"
#include "MySecondPluginManager.h"




BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPWaveformCanvas::Construct(const FArguments& InArgs)
{
	RPPMain = InArgs._RhythmPlatformingPluginMain;


	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(URPPUtility::WidgetWidth)
			.HeightOverride(URPPUtility::WidgetHeight)
			[
				SNew(SImage)
				.RenderOpacity(0.0f)
			]
		];




}

void SRPPWaveformCanvas::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

	UpperBorderSize();
	if (RPPMain)
	{
		GetBeatGrid(RPPMain->AudioCursor);
	}

}


/**
 * Sets border position. Called when constructed. Updates @Borderbox
 *
 */
void SRPPWaveformCanvas::UpperBorderSize()
{

	FVector2D ContentSize = GetCachedGeometry().GetAbsoluteSize();

	if (ContentSize.X == 0 && ContentSize.Y == 0)
	{
		return;
	}


	if ((int32)ContentSize.X == URPPUtility::WidgetWidth && (int32)ContentSize.Y == URPPUtility::WidgetHeight)
	{
		return;
	}

	if (URPPUtility::WidgetHeight == 0 && URPPUtility::WidgetWidth == 0)
	{
		return;
	}
	BoarderBox.Empty();

	URPPUtility::WidgetHeight = ContentSize.Y;
	URPPUtility::WidgetWidth = ContentSize.X;

	BorderWidth = URPPUtility::WidgetWidth;
	BorderHeight = URPPUtility::WidgetHeight;

	RPPMain->ProcessSoundWave();


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

/*given a point, it calculates the beat grid in that window.
For example, if there's beat at 3s and the window is 5s, it calculates beats within 3s to 5s.
Called every frames. */
void SRPPWaveformCanvas::GetBeatGrid(float CurrentCursor)
{

	float Padding = 0;
	float WindowLength = RPPMain->WindowLength;
	float BorderUnitPerSecond = RPPMain->PluginManagerObject->RunningSpeed;
	float AudioDuration = RPPMain->AudioDuration;
	float LineHeight = 200;

	float UnitPerSecond = URPPUtility::WidgetWidth / WindowLength; //
	float WidgetWidth = URPPUtility::WidgetWidth;

	int32 StartingIndex = 1;
	int32 LastXCord = 0;
	float LowerBound = CurrentCursor - WindowLength / 2; //where beat grid starts to render. -> left side of the screen. 
	float UpperBound = CurrentCursor + WindowLength / 2;

	if (CurrentCursor - WindowLength / 2 < WindowLength / 2)  //if cursor is less than half of window length, that means window is fill with head. No beat should be rendered.
	{
		//	return;
	}

	URPPUtility::BeatDrawArray.Empty();

	//if (CurrentCursor < WindowLength / 2) //header presented
	//{
	//	LastXCord = LastXCord + (WindowLength / 2 - CurrentCursor) * BorderUnitPerSecond;
	//}
	//else if (CurrentCursor > AudioDuration)  //cursor is beyond audio file
	//{
	//	return;
	//}
	//else                                        //default
	//{
	//	while ((URPPUtility::BeatRawArray[StartingIndex] < (LowerBound)) && (StartingIndex < URPPUtility::BeatRawArray.Num()))
	//	{
	//		StartingIndex++;
	//	}

	//	//LastXCord = LastXCord + (URPPUtility::BeatRawArray[StartingIndex - 1] - (LowerBound)) * BorderUnitPerSecond;
	//}

	while ((URPPUtility::BeatRawArray[StartingIndex] < (LowerBound)) && (StartingIndex < URPPUtility::BeatRawArray.Num()))
	{
			StartingIndex++;
	}



	while ((StartingIndex < URPPUtility::BeatRawArray.Num()) && (URPPUtility::BeatRawArray[StartingIndex] < UpperBound))
	{

		float XTemp = (URPPUtility::BeatRawArray[StartingIndex] * UnitPerSecond);
		XTemp = FMath::Fmod(XTemp, WidgetWidth);

		URPPUtility::BeatDrawArray.Add(FVector2D(XTemp, Padding));   //top point
		URPPUtility::BeatDrawArray.Add(FVector2D(XTemp, Padding) + FVector2D(0, LineHeight)); //bottom point
		StartingIndex++;
		//old

		//float XCord = LastXCord + (URPPUtility::BeatRawArray[StartingIndex] - URPPUtility::BeatRawArray[StartingIndex - 1]) * BorderUnitPerSecond;

		//URPPUtility::BeatDrawArray.Add(FVector2D(XCord, Padding));   //top point
		//URPPUtility::BeatDrawArray.Add(FVector2D(XCord, Padding) + FVector2D(0, LineHeight)); //bottom point

		//StartingIndex++;

		//LastXCord = XCord;

	}
}


/*
this function is called multiple times while on painting phase.
e.g., if theres 2 beat line in presence, BeatDrawArray will have 4 points [1top, 1bot, 2top, 2bot]
this function groups 1top and 1bot as the first line, 2top and 2 bot as the second line.
*/
void SRPPWaveformCanvas::DrawBeatGrid(float CurrentCursor, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const //CurrentCorsor feeds audiocursor
{

	for (int32 i = 0; i < URPPUtility::BeatDrawArray.Num(); i += 2)
	{
		FSlateDrawElement::MakeLines(OutDrawElements,    //render beat grid one by one
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			{ URPPUtility::BeatDrawArray[i], URPPUtility::BeatDrawArray[i + 1] },
			ESlateDrawEffect::None,
			FLinearColor::Green,
			true,
			0.5
		);
	}

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

	FSlateDrawElement::MakeLines(OutDrawElements,   //render waveform
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		URPPUtility::DrawArray,
		ESlateDrawEffect::None,
		FLinearColor::Yellow,
		true,
		0.5f
	);

	SRPPWaveformCanvas::DrawBeatGrid(RPPMain->AudioCursor, AllottedGeometry, OutDrawElements, LayerId);

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
