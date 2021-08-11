// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "VestigiumEditor.h"
#include "FootstepAssetTypeActions.h"
#include "VestigiumEditorStyle.h"


#define LOCTEXT_NAMESPACE "VestigiumEditor"

DEFINE_LOG_CATEGORY(LogVestigiumEditor);

IMPLEMENT_MODULE(FVestigiumEditor, VestigiumEditor)

/** Color to use in editor for all Vestium Assets*/
FColor FVestigiumEditor::VestigiumColor = FColor(255, 238, 0);

void FVestigiumEditor::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	UE_LOG(LogVestigiumEditor, Warning, TEXT("Vestigium Editor plugin module has started!"));

	// registers the style (sets icons)
	FVestigiumEditorStyle::Initialize();

	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// creates a category named Vestigium in the advanced assets category (rmb)
	// this uint32 may then be used by factories that want their custom type to be listed in this category as well
	GameAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Vestigium")), LOCTEXT("VestigiumCategory", "Vestigium"));

	//FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyModule.RegisterCustomClassLayout("Vestigium", FOnGetDetailCustomizationInstance::CreateStatic(&FDialoguePluginEditorSettingsDetails::MakeInstance));
	//PropertyModule.NotifyCustomizationModuleChanged();

	//EAssetTypeCategories::Type AssetCategoryBit = EAssetTypeCategories::Misc;

	//TSharedRef<IAssetTypeActions> Action = MakeShareable(new FDialogueAssetTypeActions(AssetCategoryBit));
	//RegisterAssetTypeAction(AssetTools, Action);

	// register AssetTypeActions (changes their background color)
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FFootstepAssetTypeActions(GameAssetCategory)));
}


void FVestigiumEditor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogVestigiumEditor, Warning, TEXT("Vestigium Editor plugin module has shutdown!"));
}


uint32 FVestigiumEditor::GetGameAssetCategory()
{
	if (FVestigiumEditor::Get().IsAvailable())
		return static_cast<FVestigiumEditor&>(FVestigiumEditor::Get()).GameAssetCategory;
	return 0;
}

void FVestigiumEditor::Initialize(TSharedPtr<SWindow> InRootWindow, bool bIsNewProjectWindow)
{

}
/*
void FVestigiumEditor::AddGraphicsSwitcher(FToolBarBuilder& ToolBarBuilder)
{

}

void FVestigiumEditor::ShutdownModule()
{
	FDialogueEditorStyle::Shutdown();
}

bool FVestigiumEditor::AllowAutomaticGraphicsSwitching()
{
	return bAllowAutomaticGraphicsSwitching;
}

bool FVestigiumEditor::AllowMultipleGPUs()
{
	return bAllowMultiGPUs;
}
*/
void FVestigiumEditor::RegisterAssetTypeAction(class IAssetTools& AssetTools, TSharedRef<class IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
}


#undef LOCTEXT_NAMESPACE
