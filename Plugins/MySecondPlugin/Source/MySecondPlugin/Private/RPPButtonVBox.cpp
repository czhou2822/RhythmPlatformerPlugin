// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPButtonVBox.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SRPPButtonVBox::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()   //hidden button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Reset")))
				]
			]

			+ SVerticalBox::Slot()   //Reload
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Reload")))
				]
			]

			+ SVerticalBox::Slot()   //Mark button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Mark")))
				]
			]

			+ SVerticalBox::Slot()   //Setstarting button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("StartingPosition")))
				]
			]

			+ SVerticalBox::Slot()   //SaveLevel
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("SaveLevel")))
				]
			]

			+ SVerticalBox::Slot()   //LoadLevel
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("LoadLevel")))
				]
			]

			+ SVerticalBox::Slot()   //RefreshRunningSpeed button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("RefreshRunningSpeed")))
				]
			]

			+ SVerticalBox::Slot()   //BeatStartingPoint button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("BeatStartingPoint")))
				]
			]
		];

}

void SRPPButtonVBox::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
