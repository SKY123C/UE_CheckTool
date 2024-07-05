#include "PluginLog.h"

FPluginLog::FPluginLog()
{
	RegisterLog();
}


void FPluginLog::WriteLogForAssetData(ECheckToolLog LogTypeA, const FCheckToolInstance& Instance, FString Info)
{
	for (auto LogObjectPtr : LogObjects)
	{
		if (LogTypeA == LogObjectPtr->LogType)
		{
			UObject* InObject = Instance.AssetData.GetAsset();
			TWeakObjectPtr<UObject> WeakPtr = MakeWeakObjectPtr(InObject);
			if (!LogMap.Contains(WeakPtr))
			{
				LogMap.Add(WeakPtr);
			}
			FString* InStr = LogMap.Find(WeakPtr);
			LogObjectPtr->WriteLog(*InStr, Info);
		}
	}
}

void FPluginLog::RegisterLog()
{
	LogObjects.Add(new(ErrorLogObject));
	LogObjects.Add(new(WarningLogObject));
}

FPluginLog::~FPluginLog()
{
	for (auto LogObjectPtr : LogObjects)
	{
		delete LogObjectPtr;
	}
	LogObjects.Empty();
}

FString FPluginLog::ToLog()
{
	FString OutStr;
	for (auto& Elem : LogMap)
	{
		OutStr += *Elem.Value;
	}
	return OutStr;
}

void ErrorLogObject::WriteLog(FString& InStr, FString& InMessage)
{
	FString OutStr = FString::Printf(TEXT("<p><font color = \"red\">%s</p>"), *InMessage);
	InStr += OutStr;
}

void WarningLogObject::WriteLog(FString& InStr, FString& InMessage)
{
	FString OutStr = FString::Printf(TEXT("<p><font color = \"yellow\">%s</p>"), *InMessage);
	InStr += OutStr;
}
