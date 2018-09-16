#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "ParticleObject.h"
#include "ParticleAffector.h"
#include <list>

class Particlesystem
{
private:
	//! holds the particles that are currently active
	std::list<ParticleObject*> m_particleList;

	//! dictates how many particles spawned per frame
	float m_emissionRate;
	float m_emissionCount;

	//! initial velocity of newly emitted particles
	float m_emissionLevel;

	//! the maximum number of particles active
	int m_particleCount;

	//! the maximum life of particle objects
	float m_particleLife;

	Vector3 m_position;

	//! holds the particle affectors that are applied
	std::list<ParticleAffector*> m_affectorList;

	Sprite* m_sprite;

public:
	Particlesystem(Sprite* sprite);

	//! Constructor for the Particle System
	Particlesystem(Sprite* sprite, float emissionRate, float emissionLevel, int particleCount, float maxLife = 0.0f);

	//! Add a particle affector into the particle system
	void addAffector(ParticleAffector* affector);

	//! Set the location for particle system
	void SetPos(Vector3 location);

	//! Set the maximum life of particle object
	void SetParticleLife(float life);

	//! Updates the particle system, called every frame
	void update(void);

	void draw(void);

};

#endif // !PARTICLESYSTEM_H

#pragma once
