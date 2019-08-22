// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#pragma once

#include "Vestigium.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FootstepData.h"
#include "Footstep.generated.h"


class UCharacterMovementComponent;
/**
 *	@class UFootstep
 *	@brief an AnimNotify specifically done to do calculation for footsteps sounds and footprints
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup = (Character), DontCollapseCategories)
class VESTIGIUM_API UFootstep : public UAnimNotify
{
	GENERATED_BODY()
public:

	UFootstep();

protected:

	/**
	 *	@brief bUseRayTrace
	 *	 if we should prefer raytracing to Character movement component
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep|Optimisation")
		bool bUseRayTrace;


	/**
	 *	@brief TraceLength
	 *	The Length of the raytrace to use for footsteps
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep|Optimisation", meta = (EditCondition = "bUseRayTrace"))
		float TraceLength;


	/**
	 *	@brief Intensity
	 *	 how strongly this footstep happens
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep", meta = (ExposeOnSpawn = true))
		float Intensity;

	/**
	 *	@brief FootBoneName
	 *	 Name of the bone hitting the ground
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep", meta = (ExposeOnSpawn = true))
		FName FootBoneName;

	/**
	 *	@brief FootstepAsset
	 *	 an asset describing all the asset parameter. they can be overriden directly in the anim notify
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep", meta = (ExposeOnSpawn = true))
		UFootstepData* FootstepAsset;


	//	Sound		------------------------------------------------------------------------------------------------------------

	/**
	 *	@brief bOverrideSound
	 *	 override asset sounds and replace them by @see OverrideSoundCue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Sound")
		bool bOverrideSound;

	/**
	 *	@brief OverrrideSoundCue
	 *	 The sound to play if bOverrideSound is true or if no asset is specified
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep|Sound", meta = (EditCondition = "bOverrideSound"))
		class USoundBase * SoundCueOverride;

	/**
	 *	@brief OverrideSoundConcurrencySettings
	 *	 The sound concurency to use if bOverrideSound is setS
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep|Sound", meta = (EditCondition = "bOverrideSound"))
		class 	USoundConcurrency* OverrideSoundConcurrencySettings;

	//	Particles	------------------------------------------------------------------------------------------------------------

	/**
	 *	@brief bOverrideSound
	 *	override asset sounds and replace them by @see OverrrideSoundCue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Particles")
		bool bUsesParticles;

	/**
	 *	@brief bOverrideParticles
	 *	override foot asset  and replace them by @see OverrideParticleSystem
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Particles", meta = (EditCondition = "bUsesParticles"))
		bool bOverrideParticles;

	/**
	 *	@brief OverrideParticleSystem
	 *	The Particle to play if bOverrideParticles is true
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Particles", meta = (EditCondition = "bUsesParticles && bOverrideParticles"))
		UParticleSystem * ParticleSystemOverride;


	//	Decals	------------------------------------------------------------------------------------------------------------

	/**
	 *	@brief bOverrideSound
	 *	override asset sounds and replace them by @see OverrrideSoundCue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Decals")
		bool bUsesDecals;

	/**
	 *	@brief bOverrideParticles
	 *	override foot asset  and replace them by @see OverrideParticleSystem
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Decals", meta = (EditCondition = "bUsesDecals"))
		bool bOverrideDecals;

	/**
	 *	@brief DecalOverride
	 *	The decal to Use if you override
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footstep|Decals", meta = (EditCondition = "bUsesDecals && bOverrideDecals"))
		FDecalMaterial DecalOverride;

	/**
	 *	@fn Notify
	 *	overriden from parent class
	 *	@see UAnimNotify
	 */
	virtual void Notify(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation) override;



private:

	/**
	 *	@brief WalkingSurface
	 *	 EPhysicalSurface you're currently over, updated asynchronously
	 */
	EPhysicalSurface WalkingSurface;

	/**
	 *	@brief bwantPosition boolean flag
	 *	 do we have reasons to find exact position ? ie : valid bone name and particle system to use
	 */
	UPROPERTY()
		uint32 bwantPosition : 1;


	/**
	 *	@brief GroundHeight Ground Z position
	 */
	UPROPERTY()
		float GroundHeight;

	/**
	 *	@brief GroundNormal Ground orientation
	 */
	UPROPERTY()
		FVector GroundNormal;

	/**
	 *	@brief bGroundHeigthIsValid boolean flag
	 *	Tells if GroundHeight has been updated recently
	 */
	UPROPERTY()
		uint32 bGroundInfoIsValid : 1;

#if 0
	/**
	 *	@brief FootPosition() get the Position of foot/ground collision
	 */
	UFUNCTION()
		void FootTrace(const USkeletalMeshComponent* MeshComp, FTransform &FootTransform);
#endif

	FTraceHandle	LastTraceHandle;
	FTraceDelegate	FootTraceDelegate;
	uint32			bWantsTrace : 1;

	void SetWantsTrace();
	FTraceHandle RequestTrace(const USkeletalMeshComponent * MeshComp);
	void UseTraceResults(const FTraceDatum& data);
	void OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);

	AActor * SkeletalActor;
	FTransform Bone;




protected:

	UFUNCTION(BlueprintPure, Category = "Footstep|Character")
		UCharacterMovementComponent * GetCharacterMovement(const USkeletalMeshComponent * MeshComp) const;

	/**
	 *	@brief UseCharacterMovementInfo function
	 *	Retrieve All the necessary information and spawn effects
	 */
	UFUNCTION()
		virtual void UseCharacterMovementInfo(UCharacterMovementComponent* CharacterMovementComponent, USkeletalMeshComponent* MeshComp);

	/**
	 *	@brief SpawnParticleEffect() function
	 *	do all the necessary operations to spawn particles
	 */
	UFUNCTION() //BlueprintCallable, Category = "Particles", meta = (Keywords = "particle system", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		virtual void SpawnAllEffects(const UObject* WorldContextObject, const FTransform &ToWorld, uint32 PhysicalSurfaceIndex, UObject * Outer);

	/**
	 *	@brief SpawnParticleEffect() function
	 *	do all the necessary operations to spawn particles
	 */
	UFUNCTION() //BlueprintCallable, Category = "Particles", meta = (Keywords = "particle system", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		virtual void SpawnSoundEffect(const UObject* WorldContextObject, const FTransform &ToWorld, uint32 PhysicalSurfaceIndex, UObject * Outer);

	/**
	 *	@brief SpawnParticleEffect() function
	 *	do all the necessary operations to spawn particles
	 */
	UFUNCTION() //BlueprintCallable, Category = "Particles", meta = (Keywords = "particle system", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		virtual void SpawnParticleEffect(const UObject* WorldContextObject, const FTransform &ToWorld, uint32 PhysicalSurfaceIndex, UObject * Outer);

	/**
	 *	@brief SpawnParticleEffect() function
	 *	do all the necessary operations to spawn particles
	 */
	UFUNCTION() //BlueprintCallable, Category = "Particles", meta = (Keywords = "particle system", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
		virtual void SpawnDecalEffect(const UObject* WorldContextObject, const FTransform &ToWorld, uint32 PhysicalSurfaceIndex, UObject * Outer);

	/**
	 *	@brief GetSoundBase()
	 *	Gets the sound to play based on bOverrideSound, OverrrideSoundCue and FootstepAsset
	 */
	UFUNCTION()
	virtual USoundBase * GetSoundBase(uint32 PhysicalSurfaceIndex) const;


	/**
	 *	@brief GetSoundConcurrency()
	 *	Gets the correct sound concurrency to play
	 */
	UFUNCTION()
		virtual USoundConcurrency * GetSoundConcurrency() const;


	/**
	 *	@brief GetParticleTemplate()
	 *	Gets the correct Particle template to play
	 */
	UFUNCTION()
		virtual UParticleSystem* GetParticleTemplate(uint32 PhysicalSurfaceIndex) const;


	UFUNCTION()
		virtual FDecalMaterial GetDecalMaterial (uint32 PhysicalSurfaceIndex) const;



#if WITH_EDITORONLY_DATA
protected:
	UPROPERTY(EditAnywhere, Category = "Debug" )
		bool bDebug;
#endif // WITH_EDITORONLY_DATA

#if WITH_EDITOR
	virtual void BeginDestroy() override;
#endif // WITH_EDITOR


};