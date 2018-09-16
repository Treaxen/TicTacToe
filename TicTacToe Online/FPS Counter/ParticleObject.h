#ifndef PARTICLE_OBJECT_H
#define PARTICLE_OBJECT_H

#include "GameObject.h"

class ParticleObject:public GameObject
{
private:
	Vector3 m_acceleration;
	float m_life;
	float m_initLife;
	float m_maxVelocity;

public:
	//! Default Constructor
	ParticleObject();

	//! Constructor
	ParticleObject(Sprite * sprite);

	void update();

	//! Returns the current remaining life on particle object
	float GetLife();

	//! Returns the time passed for particle object
	float GetLifePassed();

	//! Returns the initial lifetime of particle object
	float GetInitLife();

	//! Set the acceleration of particle object
	void SetAcceleration(Vector3 acceleration);

	//! Set the maximum velocity (magnitude) of particle object. Setting this to 0 would remove any limit
	void SetMaxVelocity(float magnitude);

	//! Set the lifetime of particle object in frames
	void SetLife(float life);
};

#endif