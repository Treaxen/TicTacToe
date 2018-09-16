#pragma once
#include <iostream> 
using namespace std;

class Vector3
{
public:

	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);

	//Vector3 *normalized;

	Vector3 operator+(Vector3 value);
	Vector3 operator-(Vector3 value);
	Vector3 operator*(float value);
	Vector3 operator/(float value);
	
	Vector3 Cross(const Vector3& vec);
	Vector3 Normalize();
	float Dot(const Vector3& vec);
	float Magnitude();

	//property Vector3 normalized {Vectkor3 get(); }
	friend ostream& operator<<(ostream& os, const Vector3& vec);
	

};
