// Fill out your copyright notice in the Description page of Project Settings.
#include "RPPButtonVBox.h"

#include "EditorViewportClient.h"


//user includes
#include "RPPUtility.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SRPPButtonVBox::Construct(const FArguments& InArgs)
{
	RPPMain = InArgs._RhythmPlatformingPluginMain;
	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()   //hidden button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.OnClicked(this,&SRPPButtonVBox::BackToTop)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("BackToBeginning")))
				]
			]

			+ SVerticalBox::Slot()   //Reload
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.OnClicked(this, &SRPPButtonVBox::ReloadWave)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Reset")))
				]
			]

			//+ SVerticalBox::Slot()   //Mark button
			//.VAlign(VAlign_Top)
			//.HAlign(HAlign_Left)
			//[
			//	SNew(SButton)
			//	.OnClicked(this, &SRPPButtonVBox::MarkTimeStamp)
			//	.Content()
			//	[
			//		SNew(STextBlock)
			//		.Text(FText::FromString(TEXT("Mark")))
			//	]
			//]

			//+ SVerticalBox::Slot()   //Setstarting button
			//.VAlign(VAlign_Top)
			//.HAlign(HAlign_Left)
			//[
			//	SNew(SButton)
			//	.Content()
			//	[
			//		SNew(STextBlock)
			//		.Text(FText::FromString(TEXT("StartingPosition")))
			//	]
			//]

			//+ SVerticalBox::Slot()   //SaveLevel
			//.VAlign(VAlign_Top)
			//.HAlign(HAlign_Left)
			//[
			//	SNew(SButton)
			//	.OnClicked(this, &SRPPButtonVBox::SaveLevel)
			//	.Content()
			//	[
			//		SNew(STextBlock)
			//		.Text(FText::FromString(TEXT("SaveLevel")))
			//	]
			//]

			//+ SVerticalBox::Slot()   //LoadLevel
			//.VAlign(VAlign_Top)
			//.HAlign(HAlign_Left)
			//[
			//	SNew(SButton)
			//	.OnClicked(this, &SRPPButtonVBox::LoadLevel)
			//	.Content()
			//	[
			//		SNew(STextBlock)
			//		.Text(FText::FromString(TEXT("LoadLevel")))
			//	]
			//]

			+ SVerticalBox::Slot()   //RefreshRunningSpeed button
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.OnClicked(this, &SRPPButtonVBox::RefreshRunningSpeed)
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
				.OnClicked(this, &SRPPButtonVBox::ChangeBeatStartingTime)
				.Content()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("BeatStartingPoint")))
				]
			]
		];

}

FReply SRPPButtonVBox::BackToTop()
{
	if (RPPMain)
	{
		RPPMain->ResetViewport();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SRPPButtonVBox::ReloadWave()
{
	if (RPPMain)
	{
		RPPMain->Initilization();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

//FReply SRPPButtonVBox::MarkTimeStamp()
//{
//	if (RPPMain)
//	{
//		URPPUtility::AddTimestamp(RPPMain->AudioCursor);
//		return FReply::Handled();
//	}
//	return FReply::Unhandled();
//}

FReply SRPPButtonVBox::LoadLevel()
{
	URPPUtility::LoadLevel();
	return FReply::Handled();
}

FReply SRPPButtonVBox::SaveLevel()
{
	URPPUtility::SaveLevel();
	return FReply::Handled();

}

FReply SRPPButtonVBox::RefreshRunningSpeed()
{
	if (RPPMain)
	{
		URPPUtility::RefreshRunSpeed();
		return FReply::Handled();
	}
	return FReply::Unhandled();

}

FReply SRPPButtonVBox::ChangeBeatStartingTime()
{
	if (RPPMain)
	{
		RPPMain->SetCurrentAsBeatStartingTime();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}



















END_SLATE_FUNCTION_BUILD_OPTIMIZATION

