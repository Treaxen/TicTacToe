#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"
#include "Vector3.h"
#include "Random.h"

class GameObject
{
protected:
	Sprite* m_sprite;

	Vector3 m_position;
	Vector3 m_velocity;
	float m_rotation;
	float m_scale;
	Color m_color;
	enumBlend m_blendmode;

public:
	//! Default constructor without sprite
	GameObject();

	//! Constructor with sprite
	GameObject(Sprite* sprite);

	//! Set the position of gameobject
	void SetPos(Vector3 pos);

	//! Return the position of gameobject
	const Vector3& GetPos();

	//! Set the Velocity of gameobject
	void SetVeloCity(Vector3 velo);

	//! Return the Velocity of gameobject
	const Vector3& GetVelocity();

	//! Set the Rotation of gameobject
	void SetRotation(float rotate);

	//! Get the Rotation of gameobject
	float GetRotation();

	//! Set the Scale of gameobject
	void SetScale(float scale);

	//! Get the Scale of gameobject
	float GetScale();

	//! Set the sprite of gameobject
	void SetSprite(Sprite* sprite);

	//! Return the Sprite of gameobject
	Sprite* GetSprite();

	//! Set the Color of the gameobject
	void SetColor(const Color& color);

	//! Return the Color of gameobject
	const Color& GetColor();

	//! Set the Blending mode. Available modes : Alpha, Additive, Multiply
	void setBlendingMode(enumBlend blend); //allows users to set alpha, additive and multiply blends

	//! Return the active Blending mode
	enumBlend getBlendingmode();

	void draw();
	virtual void update();
};

#endif
