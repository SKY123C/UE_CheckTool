// Copyright Epic Games, Inc. All Rights Reserved.

#include "CheckToolCommands.h"

#define LOCTEXT_NAMESPACE "FCheckToolModule"

void FCheckToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CheckTool", "Bring up CheckTool window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
