#include "TemplateClass/CheckTemplate.h"

bool UCheckToolCollection::Process_Implementation(UCheckToolContext* Context)
{
	return false;
}

bool UCheckToolValidation::Process_Implementation(const FCheckToolInstance& Instance)
{
	return false;
}

void UCheckToolValidation::AddLog(ECheckToolLog CheckToolLogType, const FCheckToolInstance& Instance, FString InStr)
{
	PluginLog.WriteLogForAssetData(CheckToolLogType, Instance, InStr);
}

FString UCheckToolValidation::ToLog()
{
	return PluginLog.ToLog();
}
