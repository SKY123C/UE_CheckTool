#include "Plugins.h"

UMyCppTestPlugin::UMyCppTestPlugin()
{

}

bool UMyCppTestPlugin::Process_Implementation(const FCheckToolInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Instance.AssetData.GetFullName())
	return false;
}
