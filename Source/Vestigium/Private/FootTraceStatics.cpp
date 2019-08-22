// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "FootTraceStatics.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "Engine/World.h"

#if WITH_EDITOR
#include "DrawDebugHelpers.h"
#endif //WITH_EDITOR


FName UFootTraceStatics::NAME_AsyncRequestTrace = "AsyncFootTrace";

FCollisionQueryParams UFootTraceStatics::ConfigureCollisionParams(const UObject* WorldContextObject, FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf)
{
	FCollisionQueryParams Params(TraceTag, SCENE_QUERY_STAT_ONLY(KismetTraceUtils), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.bReturnFaceIndex = !UPhysicsSettings::Get()->bSuppressFaceRemapTable; // Ask for face index, as long as we didn't disable globally
	Params.AddIgnoredActors(ActorsToIgnore);
	if (bIgnoreSelf)
	{
		const AActor* IgnoreActor = Cast<AActor>(WorldContextObject);
		if (IgnoreActor)
		{
			Params.AddIgnoredActor(IgnoreActor);
		}
		else
		{
			// find owner
			UObject* CurrentObject = const_cast<UObject*>(WorldContextObject);
			while (CurrentObject)
			{
				CurrentObject = CurrentObject->GetOuter();
				IgnoreActor = Cast<AActor>(CurrentObject);
				if (IgnoreActor)
				{
					Params.AddIgnoredActor(IgnoreActor);
					break;
				}
			}
		}
	}
	return Params;
}


FTraceHandle  UFootTraceStatics::RequestTrace(const UObject * WorldContextObject, const FVector &Start, const FVector &End, const TArray<AActor*>& ActorsToIgnore, FTraceDelegate &TraceDelegate, bool bDrawDebug)
{
	UWorld* World = WorldContextObject->GetWorld();
	if (World == nullptr)
		return FTraceHandle();

	//auto Channel = UEngineTypes::ConvertToCollisionChannel(ETraceTypeQuery::TraceTypeQuery1);

	ECollisionChannel Channel = ECollisionChannel::ECC_WorldStatic; // We only care about static :)

	FCollisionObjectQueryParams ObjectQueryParams(Channel);

	// Collision Response
	FCollisionResponseParams ResponseParams = FCollisionResponseParams::DefaultResponseParam;
	ResponseParams.CollisionResponse.SetAllChannels(ECollisionResponse::ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	bool bTraceComplex = false;
	bool bIgnoreSelf = true;

	auto Params = ConfigureCollisionParams(WorldContextObject, NAME_AsyncRequestTrace, bTraceComplex, ActorsToIgnore, bIgnoreSelf);

	return World->GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Single, Start, End, Channel, Params, ResponseParams, &TraceDelegate);
	//return World->AsyncLineTraceByChannel(EAsyncTraceType::Single,Start, End,Channel,Params, FCollisionResponseParams::DefaultResponseParam, FCollisionQueryParams::DefaultQueryParam, FCollisionResponseParams::DefaultResponseParam, TraceDelegate);

#if WITH_EDITOR
	if (bDrawDebug)
	{
		UE_LOG(LogVestigium, Display, TEXT("Debug Active : Trace : DrawDebugLine"));
		DrawDebugLine(
			WorldContextObject->GetWorld(),
			Start,
			End,
			FColor(255, 238, 0) ,
			false, 5.f, 100,
			30.f
		);
	}
#endif // WITH_EDITOR
}
