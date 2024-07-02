#include "CheckToolEditorSubsystem.h"
#include "Misc/ScopedSlowTask.h"
#include "AssetRegistry/AssetRegistryModule.h"

UCheckToolEditorSubsystem::UCheckToolEditorSubsystem()
{

}

void UCheckToolEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Context = UCheckToolContext::Get();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistryModule.GetRegistry().OnAssetAdded().AddUObject(this, &UCheckToolEditorSubsystem::OnAssetAdded);
}

TArray<UCheckToolPlugin*> UCheckToolEditorSubsystem::RegisterPlugins(TArray<UCheckToolPlugin*> PluginContextList)
{
	TArray<UCheckToolPlugin*> OutPlugins;
	bool Result = false;
	for (auto Plugin : PluginContextList)
	{
		if (FindPlugin(Plugin) && CheckPlugin(Plugin))
			OutPlugins.Add(Plugin);
			continue;
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
	CollectionList.Empty();
	ValidatioList.Empty();
}

void UCheckToolEditorSubsystem::Publish()
{
	Context->Clear();
	float PluginNum = CheckToolPlugins.Num();
	FScopedSlowTask Progress(PluginNum, FText::FromString("Start CheckTool"));
	Progress.MakeDialog(false, true);
	for (auto Plugin : GetPlugins(TSubclassOf<UCheckToolCollection>(UCheckToolCollection::StaticClass())))
	{
		UCheckToolCollection* Collection = Cast<UCheckToolCollection>(Plugin);
		Collection->Process(Context);
		Progress.EnterProgressFrame(1, FText::FromString(FString::Printf(TEXT("Current Task: %s"), *Collection->DisplayLabel)));
	}
	for (auto Plugin : GetPlugins(TSubclassOf<UCheckToolValidation>(UCheckToolValidation::StaticClass())))
	{
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

bool UCheckToolEditorSubsystem::FindPlugin(UCheckToolPlugin* Plugin)
{
	bool Result = false;
	UClass* InClass = Plugin->GetClass();

	Result = CheckToolPlugins.Find(Plugin) != INDEX_NONE ? true : false;
	if (InClass->IsChildOf(UCheckToolCollection::StaticClass()))
	{
		Result = CollectionList.Find(Plugin) != INDEX_NONE? true : false;

	}
	else if (InClass->IsChildOf(UCheckToolValidation::StaticClass()))
	{
		Result = ValidatioList.Find(Plugin) != INDEX_NONE ? true : false;
	}
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

	for (auto Plugin : CheckToolPlugins)
	{
		if (InClass == Plugin->GetClass())
		{
			OutPlugins.Add(Plugin);
		}
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
		Callback.ExecuteIfBound(InAssetData);
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
