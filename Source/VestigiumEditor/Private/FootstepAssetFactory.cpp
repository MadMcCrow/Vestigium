// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "FootstepAssetFactory.h"
#include "VestigiumEditor.h"

#define LOCTEXT_NAMESPACE "DialoguePluginEditor" 

UFootstepAssetFactory::UFootstepAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UFootstepData::StaticClass();
}

UObject* UFootstepAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	auto NewObjectAsset = NewObject<UFootstepData>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

uint32 UFootstepAssetFactory::GetMenuCategories() const
{
	return FVestigiumEditor::GetGameAssetCategory();
}

FText UFootstepAssetFactory::GetDisplayName() const
{
	return LOCTEXT("FootstepAsset", "UFootstepData");
}

FString UFootstepAssetFactory::GetDefaultNewAssetName() const
{
	return FString(TEXT("NewFootStepAsset"));
}

#undef LOCTEXT_NAMESPACE