#pragma once
#include "CheckToolContext.generated.h"

UCLASS(Blueprintable)
class UCheckToolContext : public UObject
{
	GENERATED_BODY()
public:
	static UCheckToolContext* Get();

	UFUNCTION(BlueprintCallable)
	void CreateInstanceData(const FCheckToolInstance& Instance);

	TArray<FCheckToolInstance>& GetInstanceList() { return InstanceList; };

	void Clear() { InstanceList.Empty(); };

	void PackageInstanceData();
private:
	TArray<FCheckToolInstance> InstanceList;
};