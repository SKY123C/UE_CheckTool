// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "CheckToolUI/SCheckTool.h"

class FToolBarBuilder;
class FMenuBuilder;

DECLARE_LOG_CATEGORY_EXTERN(CheckTool, Log, All)

class FCheckToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	TSharedPtr<SCheckToolWindow> CheckToolWidget;
	
	TSharedPtr<FCheckTooler> GetCheckTooler();
	TSharedPtr<FCheckTooler> CheckTooler;
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

};
