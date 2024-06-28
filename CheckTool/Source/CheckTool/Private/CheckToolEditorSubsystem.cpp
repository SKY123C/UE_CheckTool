#include "CheckToolEditorSubsystem.h"
#include "Misc/ScopedSlowTask.h"

UCheckToolEditorSubsystem::UCheckToolEditorSubsystem()
{
	Context = UCheckToolContext::Get();
}

void UCheckToolEditorSubsystem::RegisterPlugins(TArray<UCheckToolPlugin*> PluginContextList)
{
	for (auto Plugin : PluginContextList)
	{
		if (FindPlugin(Plugin))
			continue;
			
		UClass* InClass = Plugin->GetClass();
		if (InClass->IsChildOf(UCheckToolCollection::StaticClass()))
		{
			CollectionList.Add(Plugin);
		}
		else if (InClass->IsChildOf(UCheckToolValidation::StaticClass()))
		{
			ValidatioList.Add(Plugin);
		};
	}
	ValidatioList.Sort([](const UCheckToolPlugin& PluginA, const UCheckToolPlugin& PluginB) {
		return PluginA.Order < PluginB.Order;
	});

	CollectionList.Sort([](const UCheckToolPlugin& PluginA, const UCheckToolPlugin& PluginB) {
		return PluginA.Order < PluginB.Order;
	});
}
void UCheckToolEditorSubsystem::UnregisterPlugins(TArray<UCheckToolPlugin*> PluginContextList)
{
	for (auto Plugin : PluginContextList)
	{
		if (FindPlugin(Plugin))
		{
			UClass* InClass = Plugin->GetClass();
			if (InClass->IsChildOf(UCheckToolCollection::StaticClass()))
			{
				CollectionList.Remove(Plugin);
			}
			else if (InClass->IsChildOf(UCheckToolValidation::StaticClass()))
			{
				ValidatioList.Remove(Plugin);
			}
		}
	}
}

CHECKTOOL_API void UCheckToolEditorSubsystem::ClearAllPlugins()
{
	
	CollectionList.Empty();
	ValidatioList.Empty();
}

void UCheckToolEditorSubsystem::Publish()
{
	Context->Clear();
	float PluginNum = CollectionList.Num() + ValidatioList.Num();
	FScopedSlowTask Progress(PluginNum, FText::FromString("asdsa"));
	Progress.MakeDialog(false, true);
	for (auto Plugin : CollectionList)
	{
		UCheckToolCollection* Collection = Cast<UCheckToolCollection>(Plugin);
		Collection->Process(Context);
		Progress.EnterProgressFrame(1, FText::FromString(FString::Printf(TEXT("当前运行到 %s"), *Collection->DisplayLabel)));
	}
	for (auto Plugin : ValidatioList)
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

CHECKTOOL_API bool UCheckToolEditorSubsystem::FindPlugin(UCheckToolPlugin* Plugin)
{
	bool Result = false;
	UClass* InClass = Plugin->GetClass();
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

CHECKTOOL_API int32 UCheckToolEditorSubsystem::GetProcessNumber()
{
	return int32();
}
