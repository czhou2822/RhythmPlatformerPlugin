// Fill out your copyright notice in the Description page of Project Settings.
//user includes
#include "RPPBottomToolBox.h"

//engine includes
#include "Widgets/Layout/SConstraintCanvas.h"





BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPBottomToolBox::Construct(const FArguments& InArgs)
{
	SetVisibility(EVisibility::Visible);

	NewValue = InArgs._TestValue;
	RPPMain = InArgs._RhythmPlatformingPluginMain;

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
					SAssignNew(PlaybackRateText, STextBlock)
					.Text(FText::FromString(TEXT("Playback Speed: 1")))
				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillWidth(1.0)
				[
					SNew(SBox)
					[
						SAssignNew(PlaybackSlider, SSlider)
						.OnValueChanged(this, &SRPPBottomToolBox::HandleOnSliderChanged)
					]
				]
			]
		]

		+SConstraintCanvas::Slot()
		.Anchors(FAnchors(0.5f,0.0f))
		.Alignment(FVector2D(0.5,0.0))
		.AutoSize(true)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.OnClicked(this, &SRPPBottomToolBox::TogglePlay)
			.Text(FText::FromString(TEXT("Play/Pause")))
		]
	];
	

}

FReply SRPPBottomToolBox::TogglePlay()
{
	//UE_LOG(LogTemp, Warning, TEXT("Play/Pause TextValue: %i\n"), NewValue);

	if (RPPMain)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Play/Pause TextValue: %0.2f\n"), RPPMain->AudioCursor);
		RPPMain->TogglePlay();
	}

	return FReply::Handled();
}

void SRPPBottomToolBox::HandleOnSliderChanged(float InFloat)
{
	if (RPPMain)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Play/Pause TextValue: %0.2f\n"), RPPMain->AudioCursor);
		FText NewText = FText::FromString(FString("Playback Speed: ").Append(FString::SanitizeFloat(InFloat, 2)));

		PlaybackRateText.Get()->SetText(NewText);
			
			//PlaybackRateText.Get()->SetText(FString("Playback Speed: ").Append(FString::SanitizeFloat(InFloat, 2)));
		RPPMain->ChangePlaybackSpeed(InFloat);
	}
}




END_SLATE_FUNCTION_BUILD_OPTIMIZATION
