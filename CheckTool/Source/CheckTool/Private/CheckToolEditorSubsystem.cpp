#include "CheckToolEditorSubsystem.h"
#include "Misc/ScopedSlowTask.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Plugins.h"

void UCheckToolEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Context = UCheckToolContext::Get();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistryModule.GetRegistry().OnAssetAdded().AddUObject(this, &UCheckToolEditorSubsystem::OnAssetAdded);
}

void UCheckToolEditorSubsystem::Deinitialize()
{
	Context->RemoveFromRoot();
	Context->MarkAsGarbage();
}

TArray<UCheckToolPlugin*> UCheckToolEditorSubsystem::RegisterPlugins(TArray<UCheckToolPlugin*> PluginContextList)
{
	TArray<UCheckToolPlugin*> OutPlugins;
	for (auto Plugin : PluginContextList)
	{
		if (FindPlugin(Plugin) && CheckPlugin(Plugin))
		{
			CheckToolPlugins.Add(Plugin);
			OutPlugins.Add(Plugin);
		}
		CheckToolPlugins.Add(Plugin);
	}
	return OutPlugins;
}
TArray<UCheckToolPlugin*> UCheckToolEditorSubsystem::UnregisterPlugins(TArray<UCheckToolPlugin*> PluginContextList)
{
	TArray<UCheckToolPlugin*> OutPlugins;
	for (auto Plugin : PluginContextList)
	{
		if (FindPlugin(Plugin))
		{
			CheckToolPlugins.Remove(Plugin);
			UClass* InClass = Plugin->GetClass();
		}
		else
		{
			OutPlugins.Add(Plugin);
		}
	}
	return OutPlugins;
}

void UCheckToolEditorSubsystem::ClearAllPlugins()
{
	for (auto Plugin : CheckToolPlugins)
	{
		//Plugin->MarkAsGarbage();
	}
	CheckToolPlugins.Empty();
}

void UCheckToolEditorSubsystem::Publish()
{
	Context->Clear();
	float PluginNum = 0;
	for (auto Plugin : CheckToolPlugins)
	{
		if (Plugin->Enable)
		{
			PluginNum += 1;
		}
	}
	FScopedSlowTask Progress(PluginNum, FText::FromString("Start CheckTool"));
	Progress.MakeDialog(false, true);
	for (auto Plugin : GetPlugins(TSubclassOf<UCheckToolCollection>(UCheckToolCollection::StaticClass())))
	{
		UCheckToolCollection* Collection = Cast<UCheckToolCollection>(Plugin);
		if (!Plugin->Enable)
			continue;
		Collection->Process(Context);
		Progress.EnterProgressFrame(1, FText::FromString(FString::Printf(TEXT("Current Task: %s"), *Collection->DisplayLabel)));
	}
	for (auto Plugin : GetPlugins(TSubclassOf<UCheckToolValidation>(UCheckToolValidation::StaticClass())))
	{
		if (!Plugin->Enable)
			continue;
		for (auto& Instance : Context->GetInstanceList())
		{
			if (Instance.AssetData.IsValid() && (Plugin->Families.Find(Instance.AssetData.GetClass()->GetFName()) != INDEX_NONE || Instance.Family.IsNone()))
			{
				UCheckToolValidation* Validation = Cast<UCheckToolValidation>(Plugin);
				Validation->Process(Instance);
			}
		}
		Progress.EnterProgressFrame(1);
	}
}

void UCheckToolEditorSubsystem::Validate()
{
	for (auto Plugin : GetPlugins(TSubclassOf<UCheckToolValidation>(UCheckToolValidation::StaticClass())))
	{
		if (!Plugin->Enable)
			continue;
		for (auto& Instance : Context->GetInstanceList())
		{
			if (Instance.AssetData.IsValid() && (Plugin->Families.Find(Instance.AssetData.GetClass()->GetFName()) != INDEX_NONE || Instance.Family.IsNone()))
			{
				UCheckToolValidation* Validation = Cast<UCheckToolValidation>(Plugin);
				bool Result = Validation->Process(Instance);

			}
		}
	}
}

bool UCheckToolEditorSubsystem::FindPlugin(UCheckToolPlugin* Plugin)
{
	bool Result = false;
	UClass* InClass = Plugin->GetClass();
	Result = CheckToolPlugins.Find(Plugin) != INDEX_NONE ? true : false;
	return  Result;
}

bool UCheckToolEditorSubsystem::CheckPlugin(UCheckToolPlugin* Plugin)
{
	bool Result = true;
	UClass* InClass = Plugin->GetClass();
	for (TFieldIterator<FProperty> PropertyIt(InClass); PropertyIt; ++PropertyIt)
	{
		FProperty* Property = *PropertyIt;
		check(Property != NULL);
		if (Property->GetClass() == FObjectProperty::StaticClass())
		{
			
		}
		else if (Property->GetClass() == FNameProperty::StaticClass())
		{
			
		}
		else if (Property->GetClass() == FStrProperty::StaticClass())
		{

		}
	}
	return Result;
}

int32 UCheckToolEditorSubsystem::GetProcessNumber()
{
	return int32();
}

TArray<UCheckToolPlugin*> UCheckToolEditorSubsystem::GetPlugins(TSubclassOf<UCheckToolPlugin> PluginType, bool IsSort)
{
	TArray<UCheckToolPlugin*> OutPlugins;
	
	UClass* InClass = PluginType.Get();
	if (InClass)
	{ 
		for (auto Plugin : CheckToolPlugins)
		{
			UClass* OutClass = Plugin->GetClass();
			UE_LOG(LogTemp, Display, TEXT("%s"), *OutClass->GetName());
			if (OutClass->IsChildOf(InClass))
			{
				OutPlugins.Add(Plugin);
			}
		}
	}
	else
	{
		OutPlugins = CheckToolPlugins;
	}
	if (IsSort)
	{
		OutPlugins.Sort([](const UCheckToolPlugin& PluginA, const UCheckToolPlugin& PluginB) {
			return PluginA.Order < PluginB.Order;
			});
	}
	return OutPlugins;
}

bool UCheckToolEditorSubsystem::RegisterAssetCreatedDelegate(FCheckToolOnAssetLoaded Callback)
{
	bool Result = true;

	FDelegateHandle DelegateHandle = OnAssetAddedDelegate.AddLambda([Callback](const FAssetData& InAssetData)
	{
		FAssetData data;
		Callback.ExecuteIfBound(InAssetData.GetPackage()->GetName());
	});
	return Result;
}

bool UCheckToolEditorSubsystem::UnregisterAssetCreatedDelegate()
{
	bool Result = true;
	return Result;
}

void UCheckToolEditorSubsystem::OnAssetAdded(const FAssetData& InAssetData)
{
	OnAssetAddedDelegate.Broadcast(InAssetData);
}

void UCheckToolEditorSubsystem::ShowWindow()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
}
