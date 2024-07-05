#pragma once
#include "TemplateClass/CheckTemplate.h"
#include "CheckToolContext.h"
#include "CheckToolEditorSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCheckToolOnAssetAdded, const FAssetData&);
DECLARE_DYNAMIC_DELEGATE_OneParam(FCheckToolOnAssetLoaded, FString, PackagePath);

DECLARE_MULTICAST_DELEGATE(FValidateFinshed);
DECLARE_MULTICAST_DELEGATE(FCollectFinshed);

DECLARE_DYNAMIC_DELEGATE(FCheckToolValidateFinshed);
DECLARE_DYNAMIC_DELEGATE(FCheckToolCollectFinshed);




UCLASS(MinimalAPI)
class UCheckToolEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	UFUNCTION(BlueprintCallable)
	TArray<UCheckToolPlugin*> RegisterPlugins(TArray<UCheckToolPlugin*> PluginContextLis);

	UFUNCTION(BlueprintCallable)
	TArray<UCheckToolPlugin*> UnregisterPlugins(TArray<UCheckToolPlugin*> PluginContextLis);

	UFUNCTION(BlueprintCallable)
	void ClearAllPlugins();

	UFUNCTION(BlueprintCallable)
	void Publish();

	UFUNCTION(BlueprintCallable)
	void Validate();

	UFUNCTION(BlueprintCallable)
	bool FindPlugin(UCheckToolPlugin* Plugin);

	bool CheckPlugin(UCheckToolPlugin* Plugin);

	int32 GetProcessNumber();

	UFUNCTION(BlueprintCallable)
	TArray<UCheckToolPlugin*> GetPlugins(TSubclassOf<UCheckToolPlugin> PluginType = NULL, bool IsSort=true);

public:
	UFUNCTION(BlueprintCallable)
	bool RegisterAssetCreatedDelegate(FCheckToolOnAssetLoaded Callback);

	UFUNCTION(BlueprintCallable)
	bool UnregisterAssetCreatedDelegate();

	void OnAssetAdded(const FAssetData& InAssetData);

	UFUNCTION(BlueprintCallable)
	void ShowWindow();

private:
	//UPROPERTY()
	TArray<UCheckToolPlugin*> CheckToolPlugins;

	UCheckToolContext* Context;
	FCheckToolOnAssetAdded OnAssetAddedDelegate;
	FValidateFinshed ValidateFinshedDelegate;
	FCollectFinshed CollectFinshedDelegate;
private:
	TSharedPtr<SWindow> Window;

};