// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MySecondPluginCommands.h"

#define LOCTEXT_NAMESPACE "FMySecondPluginModule"

void FMySecondPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MySecondPlugin", "Execute MySecondPlugin action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
