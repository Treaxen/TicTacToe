#ifndef PARTICLEAFFECTOR_H
#define PARTICLEAFFECTOR_H

#include "ParticleObject.h"

class ParticleAffector
{

public:
	//! interpolate the values based on the current life of the particle
	virtual void affectParticleUpdate(ParticleObject* particle) = 0;
};

//! Affector that changes particle colors over time
class ColorAffector :public ParticleAffector
{
private:
	Color m_startColor;
	Color m_endColor;
	float m_r;
	float m_g;
	float m_b;
	float m_a;
public:

	//! Constructor. startColor : the color the particle starts with. endColor : the color the particle would interpolate towards
	ColorAffector(Color startColor, Color endColor);

	virtual void affectParticleUpdate(ParticleObject* particle); 
};

//! Affector that changes particle size over time
class ScaleAffector :public ParticleAffector
{
private:
	float m_startScale;
	float m_endScale;

public:

	//! Constructor. startScale : the scale of particle starts with. endScale : the scale the particle would interpolate towards
	ScaleAffector(float startScale, float endScale);

	virtual void affectParticleUpdate(ParticleObject* particle);
};

//! Affector that accelerates particles to a general direction or point.
class ForceAffector :public ParticleAffector
{
private:
	enum AttractionMode
	{
		GENERAL = 0,
		POINT
	};

	AttractionMode m_mode;
	Vector3 m_target;
	float m_force;


public:
	//! Constructor. Instantiates a particle system that accelerates the particles to a general direction. Attraction mode : GENERAL
	ForceAffector(Vector3 direction);

	//! Constructor. Instantiates a particle system that accelerates the particles to a point. Attraction mode : POINT
	ForceAffector(Vector3 point, float force);

	virtual void affectParticleUpdate(ParticleObject* particle);
};

#endif
#pragma once
