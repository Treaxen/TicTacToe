#ifndef SPIRTE_H
#define SPRITE_H
#define _USE_MATH_DEFINES

#include <string>
#include "Color.h"
#include <GLFW/glfw3.h>
#include "lodepng.h"
#include <iostream>
#include <math.h>

enum enumBlend
{
	alpha = 0,
	multiply,
	additive
};

const int TEXTURE_COUNT = 1;

class Sprite
{
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int mTextureID;

public:
	static Color color;
	Sprite();
	Sprite(const std::string& file);
	virtual ~Sprite();
	void draw(float x, float y, float scale = 1.0f, float rotation = 0.0f, Color color = Color::white, enumBlend blendmode = enumBlend::alpha);
};

#endif // !
