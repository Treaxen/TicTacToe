#include "Color.h"

Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);
Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
Color Color::red = Color(1.0f, 0.0f, 0.0f, 1.0f);
Color Color::green = Color(0.0f, 1.0f, 0.0f, 1.0f);
Color Color::blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
Color Color::purple = Color(1.0f, 0.0f, 1.0f, 1.0f);

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
}

Color::Color()
{
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
}
