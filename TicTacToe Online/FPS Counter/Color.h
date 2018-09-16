#ifndef COLOR_H
#define COLOR_H

class Color
{
public:

	//! RGBA fields
	float r;
	float g;
	float b;
	float a;

	//! Presets
	static Color black;
	static Color white;
	static Color red;
	static Color blue;
	static Color green;
	static Color purple;

	//! Constructor with alpha value
	Color(float r, float g, float b, float a);

	//! Constructor with only RGB value
	Color(float r, float g, float b);

	//! Default constructor
	Color();
	
};





#endif
