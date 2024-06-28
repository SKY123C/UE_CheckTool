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
	// TODO: �ڴ˴����� return ���
	InstanceList.Add(Instance);
}
