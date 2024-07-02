#include "CheckData.h"

UCheckToolContext* UCheckToolContext::Get()
{
	static UCheckToolContext* Singleton;
	if (!Singleton)
	{
		Singleton = NewObject<UCheckToolContext>();
		Singleton->AddToRoot();
	}
	return Singleton;
}

void UCheckToolContext::CreateInstanceData(const FCheckToolInstance& Instance)
{
	// TODO: 在此处插入 return 语句
	InstanceList.Add(Instance);
}
