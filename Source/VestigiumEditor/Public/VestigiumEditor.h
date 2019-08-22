// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

// Footsteps Actual classes
//#include "Vestigium.h"
#include "Footstep.h"
#include "FootstepData.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVestigiumEditor, All, All);

/**
 * The public interface to this module
 */
class IVestigiumEditor : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IVestigiumEditor& Get()
	{
		return FModuleManager::LoadModuleChecked< IVestigiumEditor >( "VestigiumEditor" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "VestigiumEditor" );
	}

};

class FVestigiumEditor : public IVestigiumEditor
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** IDialoguePluginEditorModule implementation */
	//virtual bool AllowAutomaticGraphicsSwitching() override;
	//virtual bool AllowMultipleGPUs() override;

	uint32 GameAssetCategory;

	static FColor VestigiumColor;

public:
	static uint32 GetGameAssetCategory();

private:
	void Initialize(TSharedPtr<class SWindow> InRootWindow, bool bIsNewProjectWindow);
	//void AddGraphicsSwitcher(class FToolBarBuilder& ToolBarBuilder);

private:
	void RegisterAssetTypeAction(class IAssetTools& AssetTools, TSharedRef<class IAssetTypeActions> Action);
	//TSharedPtr< class FExtender > NotificationBarExtender;
	//bool bAllowAutomaticGraphicsSwitching;
	//bool bAllowMultiGPUs;




};
