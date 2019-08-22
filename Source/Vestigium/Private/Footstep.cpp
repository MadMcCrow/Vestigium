// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Footstep.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "FootTraceStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Components/AudioComponent.h"
//#include "CollisionQueryParams.h" 

UFootstep::UFootstep() : bUseRayTrace(false), TraceLength(300), bwantPosition(true)
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 238, 0);
#endif // WITH_EDITORONLY_DATA
	Intensity = 1.f;
	WalkingSurface = EPhysicalSurface::SurfaceType_Default;

	FootBoneName = "foot_l"; // default to UE4 skeleton left foot

	bGroundInfoIsValid = false;
	GroundNormal = FVector(0.f, 0.f, 1.f);
	GroundHeight = -2.f;

	//FootTraceDelegate.BindUObject(this, &UFootstep::OnTraceCompleted);

	bOverrideSound = true;
	bOverrideParticles = true;
	

#if WITH_EDITOR
	bDebug = true;
#endif // WITH_EDITOR

}

void UFootstep::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	FootTraceDelegate.BindUObject(this, &UFootstep::OnTraceCompleted);
	// Don't call super to avoid call back in to blueprints
	//Super::Notify(MeshComp, Animation); 


	if (!MeshComp)
		return;

	const auto Loc = MeshComp->GetBoneLocation(FootBoneName); // EBoneSpaces::WorldSpace, no need to specify, i't
	const auto Rot = MeshComp->GetBoneQuaternion(FootBoneName, EBoneSpaces::WorldSpace);


	Bone = FTransform(Rot, Loc);
	
	SkeletalActor = MeshComp->GetAttachmentRootActor();
	if (!SkeletalActor)
		return;


	// Now handle the finding and use of the ground surface :
	const auto CharMov = GetCharacterMovement(MeshComp);

#if WITH_EDITOR
	if (!bUseRayTrace && !CharMov && bDebug)
		UE_LOG(LogVestigium, Error, TEXT("GetCharacterMovement : no Character movement found, please use raytrace"));
#endif //WITH_EDITOR

	if (!bUseRayTrace && CharMov)
	{
		// ensure to retrieve the data we need
		MeshComp->bReturnMaterialOnMove = true;
		const auto rootComp = Cast<UPrimitiveComponent>(SkeletalActor->GetRootComponent());
		if(rootComp)
			rootComp->bReturnMaterialOnMove = true;

		UseCharacterMovementInfo(CharMov, MeshComp);

		// no need to continue
		bWantsTrace = false;
		return; 
	}
 
	SetWantsTrace();

	if (bWantsTrace)
	{

		LastTraceHandle = RequestTrace(MeshComp);
		bWantsTrace = false;
	}
#if WITH_EDITOR
	else {
		UE_LOG(LogVestigium, Warning, TEXT("bWantsTrace was false"));
	}
#endif //WITH_EDITOR
}

void UFootstep::SetWantsTrace()
{
	if(!SkeletalActor->GetWorld())
	{
#if WITH_EDITOR
		UE_LOG(LogVestigium, Warning, TEXT("GetWorld was not retrieved"));
#endif //WITH_EDITOR
		return;
	}
	// don't allow overlapping traces here.
	if (!SkeletalActor->GetWorld()->IsTraceHandleValid(LastTraceHandle, false))
	{
		bWantsTrace = true;
	}
}

FTraceHandle UFootstep::RequestTrace(const USkeletalMeshComponent * MeshComp)
{
	const auto Loc = MeshComp->GetBoneLocation(FootBoneName);
	const auto Owner = MeshComp->GetAttachmentRootActor();
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

#if WITH_EDITOR
	return UFootTraceStatics::RequestTrace(Owner, Loc, Loc - FVector(0.f, 0.f, TraceLength), ActorsToIgnore, FootTraceDelegate, bDebug);
#else
	return UFootTraceStatics::RequestTrace(Owner, Loc, Loc - FVector(0.f, 0.f, TraceLength), ActorsToIgnore, FootTraceDelegate, false);
#endif // WITH_EDITOR
}


void UFootstep::OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
	ensure(Handle == LastTraceHandle);
	UseTraceResults(Data);
	LastTraceHandle._Data.FrameNumber = 0; // reset it
}


void UFootstep::UseTraceResults(const FTraceDatum& data)
{
	if (data.OutHits.IsValidIndex(0))
	{

		const auto hit = data.OutHits[0];
		if (hit.IsValidBlockingHit())
		{
			GroundHeight = hit.ImpactPoint.Z;
			GroundNormal = hit.ImpactNormal;

			FRotator Rotation = GroundNormal.Rotation() + FRotator(90.f,0.f, 90.f);
			const FVector Location = hit.ImpactPoint;

			const auto ToWorldUnscaled = FTransform(Rotation, Location, FVector::OneVector);

			uint32 PhysicalIndex = 0;
			if (hit.PhysMaterial.IsValid())
				PhysicalIndex = hit.PhysMaterial->SurfaceType;

#if WITH_EDITOR
			else
				UE_LOG(LogVestigium, Error, TEXT("UseTraceResults : data.OutHits[0].PhysMaterial.IsValid() returned false, physical Surface not found"));
#endif //WITH_EDITOR

			SpawnAllEffects(SkeletalActor, ToWorldUnscaled, PhysicalIndex, SkeletalActor);
		}
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogVestigium, Error, TEXT("UseTraceResults : data.OutHits.IsValidIndex(0) returned false, no hit were found between %s and %s"), *data.Start.ToString(), *data.End.ToString() );
	}
#endif //WITH_EDITOR

}

UCharacterMovementComponent* UFootstep::GetCharacterMovement(const USkeletalMeshComponent * MeshComp) const
{
	const auto Char = Cast<ACharacter>(MeshComp->GetAttachmentRootActor());
	if (!Char)
	{
		return nullptr;
	}
	return Char->GetCharacterMovement();
}

void UFootstep::UseCharacterMovementInfo(UCharacterMovementComponent* CharacterMovementComponent, USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp)
		return;

	if(!CharacterMovementComponent)
	{
#if WITH_EDITOR
		UE_LOG(LogVestigium, Warning, TEXT("UseCharacterMovementInfo : CharacterMovementComponent Not Valid, Spawning at Mesh Location instead, Couldn't retrieve Physical Surface"));
#endif //WITH_EDITOR

		FVector Loc = MeshComp->GetBoneLocation(FootBoneName);
		Loc.Z = MeshComp->GetComponentLocation().Z;
		const FQuat Rot = MeshComp->GetBoneQuaternion(FootBoneName, EBoneSpaces::WorldSpace);
		const FTransform T = FTransform(Rot, Loc);
		SpawnAllEffects(MeshComp->GetAttachmentRootActor(), T, 0, MeshComp->GetAttachmentRootActor());
	}

	// Here Character Movement is Valid :
	FHitResult HitResult = CharacterMovementComponent->CurrentFloor.HitResult;
	const FVector Normal = HitResult.Normal;
	const FVector Loc = HitResult.ImpactPoint;
	const FVector BoneLoc = MeshComp->GetBoneLocation(FootBoneName, EBoneSpaces::WorldSpace);
	const FVector BoneFV = MeshComp->GetBoneQuaternion(FootBoneName, EBoneSpaces::WorldSpace).GetForwardVector();

	// Lets project onto the ground Plane
	const FVector FinalFV = BoneFV - BoneFV.ProjectOnTo(Normal);
	const FQuat Rot = FinalFV.ToOrientationQuat();
	const FTransform T = FTransform(Rot, Loc, FVector::OneVector);


	if(HitResult.PhysMaterial.IsValid())
		SpawnAllEffects(MeshComp->GetAttachmentRootActor(), T,  (uint8)HitResult.PhysMaterial->SurfaceType, MeshComp->GetAttachmentRootActor());
	else
	{
		SpawnAllEffects(MeshComp->GetAttachmentRootActor(), T,0, MeshComp->GetAttachmentRootActor());
#if WITH_EDITOR
		UE_LOG(LogVestigium, Warning, TEXT("Mesh Does not report physical Material on Move, Please Fix"));
#endif //WITH_EDITOR
	}
}

void UFootstep::SpawnAllEffects(const UObject* WorldContextObject, const FTransform& ToWorld,
	FPlatformTypes::uint32 PhysicalSurfaceIndex, UObject* Outer)
{
	SpawnSoundEffect(WorldContextObject, ToWorld, PhysicalSurfaceIndex, Outer);
	if (bUsesParticles)
		SpawnParticleEffect(WorldContextObject, ToWorld, PhysicalSurfaceIndex, Outer);
	if (bUsesDecals)
		SpawnDecalEffect(WorldContextObject, ToWorld, PhysicalSurfaceIndex, Outer);
}

void UFootstep::SpawnParticleEffect(const UObject* WorldContextObject, const FTransform &ToWorld, uint32 PhysicalSurfaceIndex, UObject * Outer)
{
	const auto particle = GetParticleTemplate(PhysicalSurfaceIndex);
	if (!particle)
	{
		#if WITH_EDITOR
				UE_LOG(LogVestigium, Error, TEXT("SpawnParticleEffect : Could not retrieve Particle Template, failed to spawn particle"));
		#endif //WITH_EDITOR
		return;
	}
	UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, particle, ToWorld.GetLocation(), ToWorld.Rotator());
}

void UFootstep::SpawnDecalEffect(const UObject* WorldContextObject, const FTransform& ToWorld, uint32 PhysicalSurfaceIndex, UObject* Outer)
{
	const FDecalMaterial Decal = GetDecalMaterial(PhysicalSurfaceIndex);
	if (!Decal.GetDecalMaterial())
	{
#if WITH_EDITOR
		UE_LOG(LogVestigium, Error, TEXT("SpawnDecalEffect : Could not retrieve Decal Material , failed to spawn Decal"));
#endif //WITH_EDITOR
		return;
	}
		
#if !WITH_EDITOR
	UGameplayStatics::SpawnDecalAtLocation(WorldContextObject, Decal.GetDecalMaterial(), Decal.GetSize(), ToWorld.GetLocation(), FRotator(90.f, 0.f, 180.f) + ToWorld.Rotator(), Decal.GetLifetime());
#endif //!WITH_EDITOR

#if WITH_EDITOR
	if (!UGameplayStatics::SpawnDecalAtLocation(WorldContextObject, Decal.GetDecalMaterial(), Decal.GetSize(), ToWorld.GetLocation(), FRotator(90.f, 0.f, 180.f) + ToWorld.Rotator(), Decal.GetLifetime()))
		UE_LOG(LogVestigium, Error, TEXT("SpawnDecalEffect :SpawnDecalAtLocation() Did not spawn anything, something went wrong "));
#endif //WITH_EDITOR
}

void UFootstep::SpawnSoundEffect(const UObject* WorldContextObject, const FTransform &ToWorld, uint32 PhysicalSurfaceIndex, UObject * Outer)
{
	const auto SoundCue = GetSoundBase((uint8)PhysicalSurfaceIndex);
	const auto SoundConcurrencySettings = GetSoundConcurrency();

	if (SoundCue)
	{
		UGameplayStatics::PlaySoundAtLocation(WorldContextObject, SoundCue, ToWorld.GetLocation(), Intensity, 1.f, 0);
		//UAudioComponent * FootStepAudio = UGameplayStatics::SpawnSoundAtLocation(Owner, SoundCue, MeshComp->GetComponentToWorld().GetLocation(), FRotator(), Intensity, 1.f, 1.f, SoundCue->AttenuationSettings, SoundConcurrencySettings , true);
	}
#if WITH_EDITOR
	else
	{
		UE_LOG(LogVestigium, Warning, TEXT("SpawnSoundEffect : Sound failed to be spawned"));
	}
#endif //WITH_EDITOR
}



USoundBase * UFootstep::GetSoundBase(uint32 PhysicalSurfaceIndex) const
{
	if (bOverrideSound)
		return SoundCueOverride;

	if (!FootstepAsset)
	{
	#if WITH_EDITOR
		UE_LOG(LogVestigium, Warning, TEXT(" GetSoundBase : Footstep asset not set"));	
	#endif
	return SoundCueOverride;
	}

	const auto retval = FootstepAsset->GetData().GetSoundBase(PhysicalSurfaceIndex);
	
#if WITH_EDITOR
	if (!retval)
	{
		UE_LOG(LogVestigium, Error, TEXT("%s Soundbase could not get retrieved for Surface type number %d"), *FootstepAsset->GetName(), (uint8)PhysicalSurfaceIndex);
	}
#endif
	

	return retval ? retval : SoundCueOverride;

}

USoundConcurrency * UFootstep::GetSoundConcurrency() const
{
	if (bOverrideSound)
		return OverrideSoundConcurrencySettings;
	if (!FootstepAsset)
		return OverrideSoundConcurrencySettings;

	return FootstepAsset->GetData().GetSoundConcurrency();
}


UParticleSystem * UFootstep::GetParticleTemplate(uint32 PhysicalSurfaceIndex) const
{
	if (!bUsesParticles)
		return nullptr;

	if (bOverrideParticles)
		return ParticleSystemOverride;

	if (!FootstepAsset)
	{
#if WITH_EDITOR
		UE_LOG(LogVestigium, Warning, TEXT(" GetParticleTemplate : Footstep asset not set, reverting to override"));
#endif
		return ParticleSystemOverride;
	}

	return FootstepAsset->GetData().GetparticleSystem(PhysicalSurfaceIndex);
}

FDecalMaterial UFootstep::GetDecalMaterial(uint32 PhysicalSurfaceIndex) const
{
	if (!bUsesDecals)
		return nullptr;

	if (bOverrideDecals)
		return DecalOverride;

	if (!FootstepAsset)
	{
#if WITH_EDITOR
		UE_LOG(LogVestigium, Warning, TEXT(" GetDecalMaterial : Footstep asset not set, reverting to override"));
#endif
		return DecalOverride;
	}

	return FootstepAsset->GetData().GetDecalMaterial(PhysicalSurfaceIndex);
}





#if WITH_EDITOR
void UFootstep::BeginDestroy()
{
	if(bDebug)
		UE_LOG(LogVestigium, Warning, TEXT("Foot anim notify is being destroyed"));
	Super::BeginDestroy();
}
#endif //WITH_EDITOR