// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "VestigiumEditorStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

#define BOX_BRUSH( RelativePath, ... )		FSlateBoxBrush	( RootToResourcesDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define IMAGE_BRUSH( RelativePath, ... )	FSlateImageBrush( RootToResourcesDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

FString FVestigiumEditorStyle::RootToResourcesDir(const ANSICHAR* RelativePath, const TCHAR* Extension)
{
	static FString ResourcesDir = IPluginManager::Get().FindPlugin(TEXT("Vestigium"))->GetBaseDir().Append("/Resources/");
	UE_LOG(LogVestigiumEditor, Display, TEXT("Loading File :%s"), *((ResourcesDir / RelativePath) + Extension));
	return (ResourcesDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FVestigiumEditorStyle::StyleSet = nullptr;
TSharedPtr< ISlateStyle > FVestigiumEditorStyle::Get() { return StyleSet; }

FName FVestigiumEditorStyle::GetStyleSetName()
{
	static FName VestigiumEditorStyleName(TEXT("VestigiumEditorStyle"));
	return VestigiumEditorStyleName;
}

void FVestigiumEditorStyle::Initialize()
{
	 //Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	{

		StyleSet->Set(FName(TEXT("ClassThumbnail.FootstepData")), new IMAGE_BRUSH("FootstepDataAsset128", FVector2D(128, 128)));
		StyleSet->Set(FName(TEXT("ClassIcon.FootstepData")), new IMAGE_BRUSH("FootstepDataAsset16", FVector2D(16, 16)));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

#undef BOX_BRUSH
#undef IMAGE_BRUSH


void FVestigiumEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}
