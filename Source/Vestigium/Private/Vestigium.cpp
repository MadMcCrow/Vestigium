// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Vestigium.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


DEFINE_LOG_CATEGORY(LogVestigium);


class FVestigium : public IVestigium
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FVestigium, Vestigium )



void FVestigium::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	UE_LOG(LogVestigium, Warning, TEXT("Vestigium plugin module has started!"));
}


void FVestigium::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogVestigium, Warning, TEXT("Vestigium plugin module has shutdown!"));
}



