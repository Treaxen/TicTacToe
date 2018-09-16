#include "GameObject.h"

GameObject::GameObject()
{
	m_rotation = 0;
	m_scale = 1;
	m_color = Color::white;
	m_blendmode = (enumBlend)0;
}

GameObject::GameObject(Sprite * sprite)
{
	m_sprite = sprite;
	m_rotation = 0;
	m_scale = 1;
	m_color = Color::white;
	m_blendmode = (enumBlend)0;
}

void GameObject::SetPos(Vector3 pos)
{
	this->m_position = pos;
}

void GameObject::SetVeloCity(Vector3 velo)
{
	m_velocity = velo;
}

const Vector3 & GameObject::GetVelocity()
{
	return m_velocity;
}

const Vector3 & GameObject::GetPos()
{
	return this->m_position;
}

void GameObject::SetRotation(float rotate)
{
	this->m_rotation = rotate;
}

float GameObject::GetRotation()
{
	return m_rotation;
}

void GameObject::SetScale(float scale)
{
	this->m_scale = scale;
}

float GameObject::GetScale()
{
	return m_scale;
}

void GameObject::SetSprite(Sprite * sprite)
{
	this->m_sprite = sprite;
}

Sprite * GameObject::GetSprite()
{
	return this->m_sprite;
}

void GameObject::SetColor(const Color & color)
{
	this->m_color = color;
}

const Color & GameObject::GetColor()
{
	return this->m_color;
}

void GameObject::setBlendingMode(enumBlend blend)
{
	this->m_blendmode = blend;
}

enumBlend GameObject::getBlendingmode()
{
	return this->m_blendmode;
}

void GameObject::draw()
{
	m_sprite->draw(m_position.x, m_position.y, m_scale, m_rotation, m_color, m_blendmode);
}

void GameObject::update()
{
	//draw();
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
}
