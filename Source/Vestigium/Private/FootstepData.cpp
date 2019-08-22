// Noé Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "FootstepData.h"
#include "Vestigium.h"
#include "PhysicsEngine/PhysicsSettings.h"




void  FPhysicalSoundData::SetSound(USoundBase * Sound)
{
	if (Sound)
		SoundBase = Sound;
}


void FPhysicalSoundDataArray::UpdateSounds() 
{
	// Get Engine Surfaces
	auto Base = UFootstepData::GetSurfaces<FPhysicalSoundData>();

	// Store the maximums
	const uint32 origNum = PhysicalSounds.Num();
	const uint32 BaseNum = Base.Num();

	//const auto save = PhysicalSounds;
	// add default surface as first 

	for (uint32 id = 0; id < BaseNum; id++)
	{
		if(PhysicalSounds.IsValidIndex(id))
			Base[id].SetSound(PhysicalSounds[id].GetSound());
	}
	PhysicalSounds = Base;

	return;
}

#if 0
template <typename T>
void FPhysicalDataArray<T>::UpdateData()
{
	// Get Engine Surfaces
	auto Base = UFootstepData::GetSurfaces<T>();

	// Store the maximums
	const uint32 origNum = PhysicalData.Num();
	const uint32 BaseNum = Base.Num();

	//const auto save = PhysicalSounds;
	// add default surface as first 

	for (uint32 id = 0; id < BaseNum; id++)
	{
		if (PhysicalData.IsValidIndex(id))
			Base[id].SetParticle(PhysicalData[id].GetParticle());
	}
	PhysicalData = Base;
}
#endif 

void FPhysicalParticleDataArray::UpdateParticles()
{
	// Get Engine Surfaces
	auto Base = UFootstepData::GetSurfaces<FPhysicalParticleData>();

	// Store the maximums
	const uint32 origNum = PhysicalParticleSystems.Num();
	const uint32 BaseNum = Base.Num();

	//const auto save = PhysicalSounds;
	// add default surface as first 

	for (uint32 id = 0; id < BaseNum; id++)
	{
		if (PhysicalParticleSystems.IsValidIndex(id))
			Base[id].SetParticle(PhysicalParticleSystems[id].GetParticle());
	}
	PhysicalParticleSystems = Base;
}

void FPhysicalDecalDataArray::UpdateMaterials()
{
	// Get Engine Surfaces
	auto Base = UFootstepData::GetSurfaces<FPhysicalDecalData>();

	// Store the maximums
	const uint32 origNum = PhysicalDecals.Num();
	const uint32 BaseNum = Base.Num();

	//const auto save = PhysicalSounds;
	// add default surface as first 

	for (uint32 id = 0; id < BaseNum; id++)
	{
		if (PhysicalDecals.IsValidIndex(id))
			Base[id].SetMaterial(PhysicalDecals[id].GetDecalMaterial());
	}
	PhysicalDecals = Base;
}

FPhysicalParticleData FPhysicalParticleDataArray::GetParticle(EPhysicalSurface Surface) const
{
	// Todo: More efficient approach : or use find by predicate
	//Sounds[index].GetSound() : Sounds.IsValidIndex(0) ? Sounds[0].GetSound()
	for (const auto it : PhysicalParticleSystems)
	{
		if (it.GetSurface() == Surface)
			return it;
	}
	return FPhysicalParticleData();
}


FPhysicalSoundData FPhysicalSoundDataArray::GetSound(EPhysicalSurface Surface) const
{
	// Todo: More efficient approach :
	//Sounds[index].GetSound() : Sounds.IsValidIndex(0) ? Sounds[0].GetSound()
	for (const auto it : PhysicalSounds)
	{
		if (it.GetSurface() == Surface)
			return it;
	}
	return FPhysicalSoundData();
}

FPhysicalDecalData FPhysicalDecalDataArray::GetMaterial(EPhysicalSurface Surface) const
{
	// Todo: More efficient approach : or use find by predicate
//Sounds[index].GetSound() : Sounds.IsValidIndex(0) ? Sounds[0].GetSound()
	for (const auto it : PhysicalDecals)
	{
		if (it.GetSurface() == Surface)
			return it;
	}
	return FPhysicalDecalData();
}


#if WITH_EDITOR
void UFootstepData::PostEditChangeChainProperty(FPropertyChangedChainEvent & PropertyChangedEvent)
{
	Data.Sounds.UpdateSounds();
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
void UFootstepData::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Data.Sounds.UpdateSounds();
	Data.Decals.UpdateMaterials();
	Data.ParticleSystems.UpdateParticles();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif 0

uint32 UFootstepData::GetSurfacesNum()
{
	const uint32 ArrayNum = GetSurfacesNames().Num();
	return ArrayNum;
}

TArray<FName> UFootstepData::GetSurfacesNames()
{
		TArray<FName> Names;
		const auto PhysicsSettings = UPhysicsSettings::Get();
		if (!PhysicsSettings)
			return TArray<FName>();
		for (auto it : PhysicsSettings->PhysicalSurfaces)
		{
			Names.Add(it.Name);
		}
		return Names;
}



template <class T>
TArray<T> UFootstepData::GetSurfaces()
{
	// Possible safety measure :
	//static_assert(std::is_base_of<FPhysicalTypeData, T>::value, "T must inherit from FPhysicalTypeData");
	TArray<T> PhysicalArray;

	T DefaultValue("Default", EPhysicalSurface::SurfaceType_Default, nullptr);  // Always have default 
	PhysicalArray.Add(DefaultValue);

	const auto PhysicsSettings = UPhysicsSettings::Get();
	if (!PhysicsSettings)
		return PhysicalArray;

	for (auto it : PhysicsSettings->PhysicalSurfaces)
	{
		T newItem(it.Name, it.Type, nullptr); // We don't have assigned value
		PhysicalArray.Add(newItem);
	}
	return PhysicalArray;
}
