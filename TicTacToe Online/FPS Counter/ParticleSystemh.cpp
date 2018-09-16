#include "ParticleSystemh.h"

Particlesystem::Particlesystem(Sprite* sprite)
{
	m_emissionCount = 0;
	m_emissionRate = 1.0f;
	m_emissionLevel = 1.0f;
	m_particleCount = 0.0f;
	m_sprite = sprite;
}

Particlesystem::Particlesystem(Sprite* sprite, float emissionRate, float emissionLevel, int particleCount, float maxLife)
{
	m_emissionCount = 0;
	m_emissionRate = emissionRate;
	m_emissionLevel = emissionLevel;
	m_particleCount = particleCount;
	m_particleLife = maxLife;
	m_sprite = sprite;
}

void Particlesystem::addAffector(ParticleAffector * affector)
{
	ParticleAffector* newAffector = affector;

	m_affectorList.push_back(newAffector);
}

void Particlesystem::SetPos(Vector3 location)
{
	m_position = location;
}

void Particlesystem::SetParticleLife(float life)
{
	m_particleLife = life;
}

void Particlesystem::update(void)
{
	//Check if it's needed to create a new particle
	if (m_particleList.size() < m_particleCount)
	{
		m_emissionCount += m_emissionRate;
		while (m_emissionCount > 1.0f)
		{
			Vector3 v = Vector3(Random::randf(-1.0f, 1.0f), Random::randf(-1.0f, 1.0f), 0.0f); //randomize for testing
			v = v.Normalize();

			ParticleObject* newParticle = new ParticleObject(m_sprite);
			newParticle->SetPos(m_position);
			newParticle->SetVeloCity(v * m_emissionLevel);
			newParticle->SetLife(m_particleLife);
			m_particleList.push_back(newParticle);

			m_emissionCount -= 1.0f;
		}
	}

	//update the particles movement and remove dead ones
	std::list<ParticleObject*>::iterator iter = m_particleList.begin();
	while (iter != m_particleList.end())
	{
		ParticleObject* po = *iter;

		if (po->GetLife() <= 0)
		{
			ParticleObject* t_po = *iter;
			iter = m_particleList.erase(iter);
			delete t_po;
		}
		else
		{
			//traverse through each particle affector
			std::list<ParticleAffector*>::iterator iter2 = m_affectorList.begin();
			while (iter2 != m_affectorList.end())
			{
				ParticleAffector* currentAffector = *iter2;
				currentAffector->affectParticleUpdate(po);
				iter2++;
			}

			po->update();
			iter++;
		}
	}
}

void Particlesystem::draw(void)
{
	//draw particles
	std::list<ParticleObject*>::iterator iter = m_particleList.begin();

	for (iter; iter != m_particleList.end(); iter++)
	{
		ParticleObject* po = *iter;
		po->draw();
	}
}
