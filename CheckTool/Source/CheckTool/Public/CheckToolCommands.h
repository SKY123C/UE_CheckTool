// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CheckToolStyle.h"

class FCheckToolCommands : public TCommands<FCheckToolCommands>
{
public:

	FCheckToolCommands()
		: TCommands<FCheckToolCommands>(TEXT("CheckTool"), NSLOCTEXT("Contexts", "CheckTool", "CheckTool Plugin"), NAME_None, FCheckToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};