// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MySecondPluginStyle.h"

class FMySecondPluginCommands : public TCommands<FMySecondPluginCommands>
{
public:

	FMySecondPluginCommands()
		: TCommands<FMySecondPluginCommands>(TEXT("MySecondPlugin"), NSLOCTEXT("Contexts", "MySecondPlugin", "MySecondPlugin Plugin"), NAME_None, FMySecondPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
