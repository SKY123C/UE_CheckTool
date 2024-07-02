#pragma once
#include "CheckData.h"



class LogObject
{
public:
	
	ECheckToolLog LogType;
	virtual void WriteLog(FString& InStr, FString& InMessage){};
};


class ErrorLogObject : public LogObject
{
public:
	ErrorLogObject() { LogType = ECheckToolLog::Error; };
	virtual void WriteLog(FString& InStr, FString& InMessage) override;
};


class WarningLogObject : public LogObject
{
public:
	WarningLogObject(){ LogType = ECheckToolLog::Warning;};
	virtual void WriteLog(FString& InStr, FString& InMessage) override;
};


class FPluginLog
{
public:
	FPluginLog();

	void WriteLogForAssetData(ECheckToolLog LogTypeA, const FCheckToolInstance& Instance, FString Info);

	void RegisterLog();

	~FPluginLog();

	FString ToLog();
private:
	TArray<LogObject*> LogObjects;
	TMap<TWeakObjectPtr<UObject>, FString> LogMap;
};