// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "AssetTypeActions_Base.h"

class FFootstepAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FFootstepAssetTypeActions(uint32 InAssetCategory);

	// IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	//virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;
	// End of IAssetTypeActions interface

private:
	uint32 MyAssetCategory;
};
