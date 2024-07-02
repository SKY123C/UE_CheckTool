#pragma once
#include "TemplateClass/CheckTemplate.h"
#include "CheckToolEditorSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCheckToolOnAssetAdded, const FAssetData&);
DECLARE_DYNAMIC_DELEGATE_OneParam(FCheckToolOnAssetLoaded, const FAssetData&, AssetData);

UCLASS(MinimalAPI)
class UCheckToolEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	UCheckToolEditorSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API TArray<UCheckToolPlugin*> RegisterPlugins(TArray<UCheckToolPlugin*> PluginContextLis);

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API TArray<UCheckToolPlugin*> UnregisterPlugins(TArray<UCheckToolPlugin*> PluginContextLis);

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void ClearAllPlugins();

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void Publish();

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API bool FindPlugin(UCheckToolPlugin* Plugin);

	CHECKTOOL_API bool CheckPlugin(UCheckToolPlugin* Plugin);

	CHECKTOOL_API int32 GetProcessNumber();

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API TArray<UCheckToolPlugin*> GetPlugins(TSubclassOf<UCheckToolPlugin> PluginType, bool IsSort=true);

public:
	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API bool RegisterAssetCreatedDelegate(FCheckToolOnAssetLoaded Callback);

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API bool UnregisterAssetCreatedDelegate();

	void OnAssetAdded(const FAssetData& InAssetData);

	UFUNCTION(BlueprintCallable)
	CHECKTOOL_API void ShowWindow();

private:
	TArray<UCheckToolPlugin*> CollectionList;
	TArray<UCheckToolPlugin*> ValidatioList;
	TArray<UCheckToolPlugin*> CheckToolPlugins;
	UCheckToolContext* Context;
	FCheckToolOnAssetAdded OnAssetAddedDelegate;

private:
	TSharedPtr<SWindow> Window;
};