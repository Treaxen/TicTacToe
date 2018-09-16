#include "ParticleAffector.h"

ColorAffector::ColorAffector(Color startColor, Color endColor)
{
	m_startColor = startColor;
	m_endColor = endColor;

	m_r = m_endColor.r - m_startColor.r;
	m_b = m_endColor.b - m_startColor.b;
	m_g = m_endColor.g - m_startColor.g;
	m_a = m_endColor.a - m_startColor.a;
}

void ColorAffector::affectParticleUpdate(ParticleObject * particle)
{
	if (particle->GetLife() > 0)
	{
		float life = particle->GetLife();
		float initLife = particle->GetInitLife();
		Color newColor;
		if (initLife != 0)
		{
			newColor.r = m_startColor.r + ((m_r / initLife) * particle->GetLifePassed());
			newColor.g = m_startColor.g + ((m_g / initLife) * particle->GetLifePassed());
			newColor.b = m_startColor.b + ((m_b / initLife) * particle->GetLifePassed());
			newColor.a = m_startColor.a + ((m_a / initLife) * particle->GetLifePassed());

			particle->SetColor(newColor);
		}
	}
}

ScaleAffector::ScaleAffector(float startScale, float endScale)
{
	m_startScale = startScale;
	m_endScale = endScale;
}

void ScaleAffector::affectParticleUpdate(ParticleObject * particle)
{
	if (particle->GetLife() > 0)
	{
		float newScale;
		newScale = m_startScale + ((m_endScale - m_startScale) / particle->GetInitLife()) * particle->GetLifePassed();

		particle->SetScale(newScale);
	}
}

ForceAffector::ForceAffector(Vector3 direction)
{
	m_mode = AttractionMode::GENERAL;
	m_target = direction;
}

ForceAffector::ForceAffector(Vector3 point, float force)
{
	m_mode = AttractionMode::POINT;

	m_target = point;
	m_force = force;
}

void ForceAffector::affectParticleUpdate(ParticleObject * particle)
{
	Vector3 pAccel;
	
	if (m_mode == AttractionMode::GENERAL)
	{
		pAccel = m_target;
	}
	else if (m_mode == AttractionMode::POINT)
	{
		float tempX = m_target.x - particle->GetPos().x;
		float tempY = m_target.y - particle->GetPos().y;

		Vector3 tempDir = Vector3(tempX, tempY, 0.0f);
		tempDir = tempDir.Normalize();

		pAccel = tempDir * m_force;
	}

	particle->SetAcceleration(pAccel);
}

