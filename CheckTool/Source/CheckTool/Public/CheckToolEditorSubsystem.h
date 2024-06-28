#pragma once
#include "TemplateClass/CheckTemplate.h"
#include "CheckToolEditorSubsystem.generated.h"


UCLASS(MinimalAPI)
class UCheckToolEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	UCheckToolEditorSubsystem();

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void RegisterPlugins(TArray<UCheckToolPlugin*> PluginContextLis);

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void UnregisterPlugins(TArray<UCheckToolPlugin*> PluginContextLis);

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void ClearAllPlugins();

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void Publish();

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API bool FindPlugin(UCheckToolPlugin* Plugin);

	CHECKTOOL_API void CheckPlugin();

	CHECKTOOL_API int32 GetProcessNumber();


private:
	TArray<UCheckToolPlugin*> CollectionList;
	TArray<UCheckToolPlugin*> ValidatioList;
	UCheckToolContext* Context;
};