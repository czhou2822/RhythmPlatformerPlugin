// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//engine includes
#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"


//user includes
#include "RPPButtonVBox.h"
#include "RPPMainCanvas.h"

/**
 * 
 */
class MYSECONDPLUGIN_API SRPPMain : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPPMain)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

public:

	TSharedPtr<SRPPButtonVBox> RPPButtonVBox;
	TSharedPtr<SRPPMainCanvas> RPPMainCanvas;



public:
	
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // called everyframe and used for our gamelogic



};
