#pragma once
#include "TemplateClass/CheckTemplate.h"
#include "Plugins.generated.h"


UCLASS(Blueprintable)
class UMyCppTestPlugin : public UCheckToolValidation
{
	GENERATED_BODY()
public:
	UMyCppTestPlugin();
	virtual bool Process_Implementation(const FCheckToolInstance& Instance) override;
};