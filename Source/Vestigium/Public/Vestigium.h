// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Engine/EngineTypes.h"
#include "Engine/DataAsset.h"
#include "WorldCollision.h"


DECLARE_LOG_CATEGORY_EXTERN(LogVestigium, All, All);

/**
 * The public interface to this module
 */
class IVestigium : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IVestigium& Get()
	{
		return FModuleManager::LoadModuleChecked< IVestigium >( "Vestigium" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "Vestigium" );
	}
};

