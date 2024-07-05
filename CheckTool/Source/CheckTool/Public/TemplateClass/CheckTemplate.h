#pragma once
#include "CoreMinimal.h"
#include "CheckData.h"
#include "CheckToolContext.h"
#include "PluginLog.h"
#include "CheckTemplate.generated.h"


UCLASS(abstract)
class UCheckToolPlugin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Base", meta = (EditCondition = "true"))
	FString Owner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base", meta = (EditCondition = "true"))
	FString DisplayLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base", meta = (EditCondition = "true"))
	TArray<FName> Families;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base")
	bool Enable = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base", meta = (EditCondition = "true"))
	float Order = 0.0f;

};


UCLASS(Blueprintable)
class UCheckToolCollection : public UCheckToolPlugin
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Extend", meta = (ContentDir))
	FDirectoryPath Path;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Process(UCheckToolContext* Context);
	virtual bool Process_Implementation(UCheckToolContext* Context);
};


UCLASS(Blueprintable)
class UCheckToolValidation : public UCheckToolPlugin
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Process(const FCheckToolInstance& Instance);
	virtual bool Process_Implementation(const FCheckToolInstance& Instance);

public:
	FPluginLog PluginLog;
public:
	UFUNCTION(BlueprintCallable)
	void AddLog(ECheckToolLog CheckToolLogType, const FCheckToolInstance& Instance, FString InStr);

	UFUNCTION(BlueprintCallable)
	FString ToLog();
};