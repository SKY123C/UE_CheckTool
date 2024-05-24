#pragma once
#include "TemplateClass/CheckTemplate.h"
#include "CheckToolBPLib.generated.h"

UCLASS(Blueprintable)
class UCheckToolBPLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void Test();

	UFUNCTION(BlueprintCallable)
	static void RegisterPlugins(TArray<TSubclassOf<UCheckToolContext>> PluginContextLis);
};