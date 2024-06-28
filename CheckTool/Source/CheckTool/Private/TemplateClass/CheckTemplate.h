#pragma once
#include "CoreMinimal.h"
#include "CheckData.h"
#include "CheckTemplate.generated.h"


UCLASS(abstract)
class UCheckToolPlugin : public UObject
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Owner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DisplayLabel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> Families;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Enable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Order;

};


UCLASS(Blueprintable)
class UCheckToolCollection : public UCheckToolPlugin
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Path;

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
};