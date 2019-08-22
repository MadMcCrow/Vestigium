// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#pragma once



#include "Vestigium.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FootstepData.generated.h"

class UMaterialInterface;
class USoundBase;
class USoundConcurrency;
#if 0
class UNiagaraSystem;
#endif // USENIAGARA
class UParticleSystem;




/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType, Atomic)
struct VESTIGIUM_API FPhysicalParticleData
{
	GENERATED_BODY()

protected:
	/**	@brief SurfaceName PhysicalSurface name found on Engine settings	*/
	UPROPERTY(BlueprintReadOnly)
		FName SurfaceName;

	/**	@brief SurfaceType  PhysicalSurface enum for comparison				*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TEnumAsByte<EPhysicalSurface> SurfaceType;

	/**	@brief ParticleSystem UParticleSystem Particle effect associated	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem * ParticleSystem;

public:

	FPhysicalParticleData(FName Name = FName("None"), EPhysicalSurface Surface = EPhysicalSurface::SurfaceType_Default,
	                      UParticleSystem* Particle = nullptr) : SurfaceName(Name), SurfaceType(Surface),
	                                                             ParticleSystem(Particle)
	{
	}

	// Setter
	void SetParticle(UParticleSystem * Particle) { ParticleSystem = Particle; }

	// Inline getters -----------------------------------------------------------------------------------------------

	/**	 @brief GetSound() USoundBase Getter			*/
	FORCEINLINE UParticleSystem * GetParticle() const { return ParticleSystem; }
	/**	 @brief GetSurface() EPhysicalSurface Getter	*/
	FORCEINLINE EPhysicalSurface GetSurface() const { return SurfaceType; }
	/**	 @brief GetSurfaceName() Surface Name Getter	*/
	FORCEINLINE FName GetSurfaceName()	const { return SurfaceName; }
};

/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType, Atomic)
struct VESTIGIUM_API FDecalMaterial
{
	GENERATED_BODY()

protected:
	/**	@brief DecalMaterial MaterialInterface for Decal			*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface * DecalMaterial;

	/**	@brief Size FVector scale size of Decal						*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Size;

	/**	@brief Lifetime float time in seconds for Decal to exist	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Lifetime;
public:

	FDecalMaterial(UMaterialInterface * Material = nullptr, float Lifespan = 1.f, FVector Scale = FVector(1.f)) : DecalMaterial(Material), Size(Scale), Lifetime(Lifespan)
	{
	}

	FDecalMaterial(const FDecalMaterial &Src)
	{
		DecalMaterial = Src.DecalMaterial;
		Size = Src.Size;
		Lifetime = Src.Lifetime;
	}
	
	/**	 @brief GetSound() USoundBase Getter			*/
	FORCEINLINE UMaterialInterface * GetDecalMaterial() const { return DecalMaterial; }
	/**	 @brief GetSurfaceName() Surface Name Getter	*/
	FORCEINLINE float GetLifetime()	const { return Lifetime; }
	/**	 @brief GetSurfaceName() Surface Name Getter	*/
	FORCEINLINE FVector GetSize()	const { return Size; }
};

/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType, Atomic)
struct VESTIGIUM_API FPhysicalDecalData
{
	GENERATED_BODY()

protected:
	/**	@brief SurfaceName PhysicalSurface name found on Engine settings	*/
	UPROPERTY(BlueprintReadOnly)
		FName SurfaceName;

	/**	@brief SurfaceType  PhysicalSurface enum for comparison				*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TEnumAsByte<EPhysicalSurface> SurfaceType;

	/**	@brief DecalMaterial MaterialInterface for Decal associated			*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDecalMaterial DecalMaterial;


public:

	FPhysicalDecalData(FName Name = FName("None"), EPhysicalSurface Surface = EPhysicalSurface::SurfaceType_Default,
		FDecalMaterial Decal = FDecalMaterial()) : SurfaceName(Name), SurfaceType(Surface),
		DecalMaterial(Decal)
	{
	}

	// Setter
	void SetMaterial(FDecalMaterial Decal) { DecalMaterial = Decal; }

	// Inline getters -----------------------------------------------------------------------------------------------

	/**	 @brief GetSound() USoundBase Getter			*/
	FORCEINLINE FDecalMaterial  GetDecalMaterial() const { return DecalMaterial; }
	/**	 @brief GetSurface() EPhysicalSurface Getter	*/
	FORCEINLINE EPhysicalSurface GetSurface() const { return SurfaceType; }
	/**	 @brief GetSurfaceName() Surface Name Getter	*/
	FORCEINLINE FName GetSurfaceName()	const { return SurfaceName; }


};




/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType, Atomic)
struct VESTIGIUM_API FPhysicalSoundData
{

	GENERATED_BODY()

protected:
	/**	@brief SurfaceName PhysicalSurface name found on Engine settings	*/
	UPROPERTY(BlueprintReadOnly)
		FName SurfaceName;

	/**	@brief SurfaceType  PhysicalSurface enum for comparison				*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TEnumAsByte<EPhysicalSurface> SurfaceType;

	/**	@brief SurfaceName PhysicalSurface name found on Engine settings	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase *  SoundBase;

public:

	FPhysicalSoundData(FName Name = FName("None"), EPhysicalSurface Surface = EPhysicalSurface::SurfaceType_Default, USoundBase * Sound = nullptr) : SurfaceName(Name), SurfaceType(Surface), SoundBase(Sound)
	{
	}

	void SetSound(USoundBase * Sound);

	// Inline getters -----------------------------------------------------------------------------------------------

	/**	 @brief GetSound() USoundBase Getter			*/
	FORCEINLINE USoundBase * GetSound() const		{ return SoundBase;		}
	/**	 @brief GetSurface() EPhysicalSurface Getter	*/
	FORCEINLINE EPhysicalSurface GetSurface() const { return SurfaceType;	}
	/**	 @brief GetSurfaceName() Surface Name Getter	*/
	FORCEINLINE FName GetSurfaceName()	const		{ return SurfaceName;	}
};


// Sadly the UE4 does not support deriving UStruct from template structs
#if 0
/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
template<typename  T>
struct FPhysicalDataArray
{
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditFixedOrder))
		TArray<T> PhysicalData;

public:

	FPhysicalDataArray()
	{
		UpdateData();
	}

	void UpdateData();
	FPhysicalSoundData GetData(EPhysicalSurface Surface) const;

	// Inline functions
	FORCEINLINE TArray<FPhysicalSoundData> GetDataArray() const { return PhysicalData; }
	FORCEINLINE bool IsValidIndex(uint32 index) const { return PhysicalData.IsValidIndex(index); }
	FORCEINLINE FPhysicalSoundData& operator[](int32 Index) { return PhysicalData[Index]; }
	FORCEINLINE const FPhysicalSoundData& operator[](int32 Index) const { return PhysicalData[Index]; }
};
#endif


/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType)
struct VESTIGIUM_API FPhysicalParticleDataArray  // : public FPhysicalDataArray<FPhysicalParticleData>
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditFixedOrder))
		TArray<FPhysicalParticleData> PhysicalParticleSystems;

public:

	FPhysicalParticleDataArray()
	{
		UpdateParticles();
	}

	void UpdateParticles();
	FPhysicalParticleData GetParticle(EPhysicalSurface Surface) const;

	// Inline functions
	FORCEINLINE TArray<FPhysicalParticleData> GetParticles() const { return PhysicalParticleSystems; }
	FORCEINLINE bool IsValidIndex(uint32 index) const { return PhysicalParticleSystems.IsValidIndex(index); }
	FORCEINLINE FPhysicalParticleData& operator[](int32 Index) { return PhysicalParticleSystems[Index]; }
	FORCEINLINE const FPhysicalParticleData& operator[](int32 Index) const { return PhysicalParticleSystems[Index]; }
};



/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType)
struct VESTIGIUM_API FPhysicalSoundDataArray // : public FPhysicalDataArray<FPhysicalSoundData>
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditFixedOrder))
		TArray<FPhysicalSoundData> PhysicalSounds;

public:

	FPhysicalSoundDataArray()
	{
		UpdateSounds();
	}

	void UpdateSounds();
	FPhysicalSoundData GetSound(EPhysicalSurface Surface) const;

	// Inline functions
	FORCEINLINE TArray<FPhysicalSoundData> GetSounds() const { return PhysicalSounds; }
	FORCEINLINE bool IsValidIndex(uint32 index) const { return PhysicalSounds.IsValidIndex(index); }
	FORCEINLINE FPhysicalSoundData& operator[](int32 Index) { return PhysicalSounds[Index]; }
	FORCEINLINE const FPhysicalSoundData& operator[](int32 Index) const { return PhysicalSounds[Index]; }
};


/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType)
struct VESTIGIUM_API FPhysicalDecalDataArray // : public FPhysicalDataArray<FPhysicalParticleData>
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditFixedOrder), Category = "Decals")
		TArray<FPhysicalDecalData> PhysicalDecals;

public:

	FPhysicalDecalDataArray()
	{
		UpdateMaterials();
	}

	void UpdateMaterials();
	FPhysicalDecalData GetMaterial(EPhysicalSurface Surface) const;

	// Inline functions
	FORCEINLINE TArray<FPhysicalDecalData> GetMaterials() const { return PhysicalDecals; }
	FORCEINLINE bool IsValidIndex(uint32 index) const { return PhysicalDecals.IsValidIndex(index); }
	FORCEINLINE FPhysicalDecalData& operator[](int32 Index) { return PhysicalDecals[Index]; }
	FORCEINLINE const FPhysicalDecalData& operator[](int32 Index) const { return PhysicalDecals[Index]; }
};



/**
*	@brief FFootstepEffectData Asset Struct
*	Store all valid information about a footstep
*/
USTRUCT(Blueprintable, BlueprintType)
struct VESTIGIUM_API FFootstepEffectData : public FTableRowBase
{
	GENERATED_BODY()

protected:

	// Sound		-----------------------------------------------------------------------------------------------------------------------

	/**
	 *	@brief Footsteps sounds
	 *	Array of all the sounds, one for each Physical Surface type
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (ShowOnlyInnerProperties))
		FPhysicalSoundDataArray Sounds;

	/**
	 *	@brief boolean flag to avoid using ConcurrencySetting
	 *	Instead we use default sound concurrency
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (DisplayName = "Use Default Sound Concurrency Settings"))
		bool bDontUseSoundConcurrency;

	/**
	 *	@brief ConcurrencySetting
	 *	Concurrency setting override for this sound to play
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (EditCondition = "!bDontUseSoundConcurrency"))
		USoundConcurrency * ConcurrencySetting;

	// Decals		-----------------------------------------------------------------------------------------------------------------------

	/**
	 *	@brief bUseParticles boolean flag to avoid using particles
	 *	Set to true to use particles
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decals", meta = (DisplayName = "Use Decals"))
		bool bUseDecals;


	/**
	 *	@brief Footprints decal
	 *	Array of all the decals, one for each Physical Surface type
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decals", meta = (ShowOnlyInnerProperties, EditCondition = "bUseDecals"))
		FPhysicalDecalDataArray Decals;


	// Particles	-----------------------------------------------------------------------------------------------------------------------

#if 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
		bool bUseCascadeParticles = true;
#endif // USENIAGARA


	/**
	 *	@brief bUseParticles boolean flag to avoid using particles
	 *	Set to true to use particles
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles", meta = (DisplayName = "Use Particle system"))
		bool bUseParticles;

	/**
	 *	@brief ParticleSystem Footstep particle system
	 *	for now only one system is supported so you will need to combine all your emitters in one
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties, EditCondition = "bUseParticles"), Category = "Particles")
		FPhysicalParticleDataArray ParticleSystems;
#if 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUseParticles && !bUseCascadeParticles"), Category = "Particles")
		UNiagaraSystem * NiagaraParticles;
#endif // USENIAGARA

public :

	// Constructor
	FFootstepEffectData() : FTableRowBase(), bDontUseSoundConcurrency(true), bUseParticles(false)
	{
		// Create enough entries
		Sounds.UpdateSounds(); // that's it !
		ParticleSystems.UpdateParticles();
	}


	// inline getter functions

	/**	Sound Getter by index		*/
	FORCEINLINE USoundBase * GetSoundBase(uint32 index = 0) const			{ return  Sounds.IsValidIndex(index) ? Sounds[index].GetSound(): nullptr;}
	/**	Particle Getter by index	*/
	FORCEINLINE UParticleSystem * GetparticleSystem(uint32 index = 0) const	{ return ParticleSystems.IsValidIndex(index) ? ParticleSystems[index].GetParticle() : nullptr; }
	/**	Particle Getter by index	*/
	FORCEINLINE FDecalMaterial GetDecalMaterial(uint32 index = 0) const { return Decals.IsValidIndex(index) ? Decals[index].GetDecalMaterial() : nullptr; }
	/**	Sound Getter by Surface		*/
	FORCEINLINE USoundBase * GetSoundBase(EPhysicalSurface Surface) const			{ return  Sounds.GetSound(Surface).GetSound(); }
	/**	Particle Getter by Surface	*/
	FORCEINLINE UParticleSystem * GetparticleSystem(EPhysicalSurface Surface) const	{ return ParticleSystems.GetParticle(Surface).GetParticle(); }
	/**	Particle Getter by Surface	*/
	FORCEINLINE FDecalMaterial GetDecalMaterial(EPhysicalSurface Surface) const { return Decals.GetMaterial(Surface).GetDecalMaterial(); }

	/**	Sound concurrency getter	*/
	FORCEINLINE USoundConcurrency * GetSoundConcurrency() const		{ return bDontUseSoundConcurrency ? nullptr : ConcurrencySetting; }

	friend UFootstepData;
};


/**
 *	@class UFootstepData 
 *	Storage class for  @see FFootstepEffectData struct;
 */
UCLASS(BlueprintType, hidecategories = Object, editinlinenew, Category = "Vestigium", 
	meta = (DisplayName ="FootstepData"), AutoExpandCategories = (FootstepData, PhysicalSoundData, FootstepEffectData , Sound, Particles, Decals),
	Config = FootSteps)
class VESTIGIUM_API UFootstepData final: public UDataAsset // derive from UPrimaryDataAsset to gain further data asset support  
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
		FFootstepEffectData Data;

public :
	UFUNCTION(BlueprintPure)
		FORCEINLINE FFootstepEffectData GetData() const { return Data; }

#if WITH_EDITOR
	void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;

	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // 0

	template<class T>
	static TArray<T> GetSurfaces();
	static uint32 GetSurfacesNum();
	static TArray<FName> GetSurfacesNames();


	
};
