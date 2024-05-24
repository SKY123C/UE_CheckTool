#pragma once
#include "CoreMinimal.h"
#include "CheckTemplate.generated.h"


UCLASS(abstract)
class UCheckToolContext : public UObject
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite)
	FString Owner;

	UPROPERTY(BlueprintReadWrite)
	FString DisplayLabel;

	UPROPERTY(BlueprintReadWrite)
	TArray<UClass*> Families;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Process();
	virtual bool Process_Implementation();

};


UCLASS(Blueprintable)
class UCheckToolCollection : public UCheckToolContext
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Path;
};


UCLASS(Blueprintable)
class UCheckToolValidation : public UCheckToolContext
{
	GENERATED_BODY()

};