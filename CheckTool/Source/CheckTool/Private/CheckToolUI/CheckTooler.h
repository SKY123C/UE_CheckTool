#pragma once
#include "CoreMinimal.h"
#include "TemplateClass/CheckTemplate.h"

class FCheckTooler
	: public FGCObject
	, public TSharedFromThis<FCheckTooler>

{
public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override { };
	virtual FString GetReferencerName() const override { return TEXT("FCheckTooler");};
	TArray<UCheckToolCollection*> CollectionList;
	TArray<UCheckToolValidation*> ValidatioList;
	
};