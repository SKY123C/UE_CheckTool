// Copyright Epic Games, Inc. All Rights Reserved.

#include "CheckTool.h"
#include "CheckToolStyle.h"
#include "CheckToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "CheckToolUI/SCheckTool.h"
#include "ToolMenus.h"

static const FName CheckToolTabName("CheckTool");

#define LOCTEXT_NAMESPACE "FCheckToolModule"

void FCheckToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCheckToolStyle::Initialize();
	FCheckToolStyle::ReloadTextures();

	FCheckToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCheckToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCheckToolModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCheckToolModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CheckToolTabName, FOnSpawnTab::CreateRaw(this, &FCheckToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCheckToolTabTitle", "CheckTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	CheckTooler = MakeShareable(new FCheckTooler);
}

void FCheckToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCheckToolStyle::Shutdown();

	FCheckToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CheckToolTabName);
}

TSharedRef<SDockTab> FCheckToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCheckToolModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CheckTool.cpp"))
		);
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SAssignNew(CheckToolWidget, SCheckToolWindow, CheckTooler.ToSharedRef())
		];
}

void FCheckToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CheckToolTabName);
}

TSharedPtr<FCheckTooler> FCheckToolModule::GetCheckTooler()
{
	return CheckTooler;
}

void FCheckToolModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCheckToolCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCheckToolCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCheckToolModule, CheckTool)