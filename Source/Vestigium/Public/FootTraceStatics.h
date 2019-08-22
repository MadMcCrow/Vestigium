// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Vestigium.h"
#include "FootTraceStatics.generated.h"

/**
 *	Static Class for doing Async traces without 
 */
UCLASS()
class UFootTraceStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	static FName NAME_AsyncRequestTrace;

	// UFUNCTION(BlueprintPure, Category = "FootTrace", meta = (WorldContext = "WorldContextObject"))
	static FCollisionQueryParams ConfigureCollisionParams(const UObject* WorldContextObject, FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf = true);
	
	// UFUNCTION(BlueprintCallable, Category = "FootTrace", meta = (WorldContext = "WorldContextObject"))
	static FTraceHandle RequestTrace(const UObject * WorldContextObject, const FVector &Start, const FVector &End, const TArray<AActor*>& ActorsToIgnore, FTraceDelegate &TraceDelegate, bool bDrawDebug = false);

};
