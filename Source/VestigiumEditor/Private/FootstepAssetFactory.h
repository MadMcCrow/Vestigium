// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#pragma once

#include "Factories/Factory.h"
#include "FootstepAssetFactory.generated.h"

/**
 *  @class UFootstepAssetFactory
 *	Generator for the asset to allow you to create footsteps Asset in Editor
 */
UCLASS()
class VESTIGIUMEDITOR_API UFootstepAssetFactory : public UFactory
{
	GENERATED_BODY()

		UFootstepAssetFactory(const FObjectInitializer& ObjectInitializer);

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface

	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;
	virtual FString GetDefaultNewAssetName() const override;
};
