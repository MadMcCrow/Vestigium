// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once
#include "CoreMinimal.h"

class FVestigiumEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static TSharedPtr< class ISlateStyle > Get();
	static FName GetStyleSetName();
private:
	static FString RootToResourcesDir(const ANSICHAR* RelativePath, const TCHAR* Extension);
	static TSharedPtr< class FSlateStyleSet > StyleSet;
};
