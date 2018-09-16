#include "ParticleObject.h"

ParticleObject::ParticleObject() :GameObject()
{

}

ParticleObject::ParticleObject(Sprite * sprite) : GameObject(sprite)
{

}

void ParticleObject::update()
{
	//update position -> acceleration affects velocity, velocity affects position
	m_velocity = m_velocity + m_acceleration;
	
	GameObject::update();

	//decrease the life of particle every update
	m_life--;
}

float ParticleObject::GetLife()
{
	return m_life;
}

float ParticleObject::GetLifePassed()
{
	float passed = m_initLife - m_life;

	return passed;
}

float ParticleObject::GetInitLife()
{
	return m_initLife;
}

void ParticleObject::SetAcceleration(Vector3 acceleration)
{
	m_acceleration = acceleration;
}

void ParticleObject::SetMaxVelocity(float magnitude)
{
	m_maxVelocity = magnitude;
}

void ParticleObject::SetLife(float life)
{
	m_life = life;
	m_initLife = life;
}

