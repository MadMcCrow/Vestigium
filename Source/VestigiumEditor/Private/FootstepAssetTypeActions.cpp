// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "FootstepAssetTypeActions.h"
#include "VestigiumEditor.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"


FFootstepAssetTypeActions::FFootstepAssetTypeActions(uint32 InAssetCategory) : MyAssetCategory(InAssetCategory)
{
}

FText FFootstepAssetTypeActions::GetName() const
{
	return LOCTEXT("FFootstepAssetTypeActionsName", "FootStep");
}

FColor FFootstepAssetTypeActions::GetTypeColor() const
{
	return FVestigiumEditor::VestigiumColor;
}

UClass* FFootstepAssetTypeActions::GetSupportedClass() const
{
	return UFootstepData::StaticClass();
}

/*
void FFootstepAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UFootstepData* Footstep = Cast<UFootstepData>(*ObjIt))
		{
			TSharedRef<FDialogueEditor> NewDialogueEditor(new FDialogueEditor());
			NewDialogueEditor->InitDialogueEditor(Mode, EditWithinLevelEditor, Dialogue);
		}
	}
}
*/

uint32 FFootstepAssetTypeActions::GetCategories()
{
	return MyAssetCategory; //affects filters
}

#undef LOCTEXT_NAMESPACE
