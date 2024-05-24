#include "CheckToolBPLib.h"
#include "TemplateClass/CheckTemplate.h"
#include "CheckTool.h"
#include "Modules/ModuleManager.h"

void UCheckToolBPLib::Test()
{
	// 查找所有当前UObject实例
	for (TObjectIterator<UObject> It; It; ++It)
	{
		UObject* CurrentObject = *It;
		if (CurrentObject->GetClass()->IsChildOf(UCheckToolCollection::StaticClass()))
		{
			UCheckToolCollection* a = Cast<UCheckToolCollection>(CurrentObject);
			a->Process();
			UE_LOG(LogTemp, Warning, TEXT("%s"), *a->DisplayLabel);
		}
	}

}

void UCheckToolBPLib::RegisterPlugins(TArray<TSubclassOf<UCheckToolContext>> PluginContextList)
{
	FCheckToolModule& Module = FModuleManager::Get().GetModuleChecked<FCheckToolModule>(TEXT("CheckTool"));

	for (auto ContextClass : PluginContextList)
	{
		UClass* InClass = ContextClass.Get();
		UCheckToolContext* ContextPlugin = NewObject<UCheckToolContext>(GetTransientPackage(), InClass);
		if (InClass->IsChildOf(UCheckToolCollection::StaticClass()))
		{
			Module.GetCheckTooler()->CollectionList.Add(Cast<UCheckToolCollection>(ContextPlugin));
		}
		else if (InClass->IsChildOf(UCheckToolValidation::StaticClass()))
		{
			Module.GetCheckTooler()->ValidatioList.Add(Cast<UCheckToolValidation>(ContextPlugin));
		};
	}

}
