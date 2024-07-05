#pragma once
#include "CheckData.generated.h"


USTRUCT(BlueprintType)
struct FCheckToolInstance
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAssetData AssetData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Family;
};

UCLASS(Blueprintable)
class UCheckToolContext : public UObject
{
	GENERATED_BODY()
public:
	static UCheckToolContext* Get();

	UFUNCTION(BlueprintCallable)
	void CreateInstanceData(const FCheckToolInstance& Instance);
	
	TArray<FCheckToolInstance>& GetInstanceList(){return InstanceList;};

	void Clear(){ InstanceList.Empty(); };

	void PackageInstanceData();
private:
	TArray<FCheckToolInstance> InstanceList;
};

UENUM(BlueprintType)
enum class ECheckToolLog : uint8
{
	Error,
	Warning,
};