#include "Vector3.h"
#include <iostream>

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::operator+(Vector3 value)
{
	Vector3 tempClass;
	tempClass.x = x + value.x;
	tempClass.y = y + value.y;
	tempClass.z = z + value.z;

	return tempClass;
}

Vector3 Vector3::operator-(Vector3 value)
{
	Vector3 tempClass;
	tempClass.x = x - value.x;
	tempClass.y = y - value.y;
	tempClass.z = z - value.z;

	return tempClass;
}

Vector3 Vector3::operator*(float value)
{
	Vector3 tempClass;
	tempClass.x = x * value;
	tempClass.y = y * value;
	tempClass.z = z * value;

	return tempClass;
}

Vector3 Vector3::operator/(float value)
{
	Vector3 tempClass;
	tempClass.x = x / value;
	tempClass.y = y / value;
	tempClass.z = z / value;

	return tempClass;
}

ostream& operator<< (ostream& os, const Vector3& vec)
{
	os << vec.x << ", " << vec.y << " ," << vec.z;

	return os;
}

float Vector3::Magnitude()
{
	float mag;
	mag = x*x + y*y + z*z;

	if (mag != 0)
		mag = sqrt(mag);

	return mag;
}

Vector3 Vector3::Normalize()
{
	float mag;
	mag = Magnitude();

	Vector3 tempVector;
	tempVector = Vector3(x, y, z) / mag;

	return tempVector;
}

float Vector3::Dot(const Vector3& vec)
{
	float dot = (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);

	return dot;
}

Vector3 Vector3::Cross(const Vector3& vec)
{
	Vector3 cross;

	cross.x = (this->y * vec.z) - (this->z * vec.y);
	cross.y = (this->z * vec.x) - (this->x * vec.z);
	cross.z = (this->x * vec.z) - (this->z * vec.x);

	return cross;
}
