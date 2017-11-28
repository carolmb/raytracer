#include "util/OBJ_Loader.h"

#include <math.h>

objl::Vector3 objl::math::CrossV3(const objl::Vector3 a, const objl::Vector3 b)
{
	return objl::Vector3(a.Y * b.Z - a.Z * b.Y,
		a.Z * b.X - a.X * b.Z,
		a.X * b.Y - a.Y * b.X);
}

// Vector3 Magnitude Calculation
float objl::math::MagnitudeV3(const objl::Vector3 in)
{
	return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
}

// Vector3 DotProduct
float objl::math::DotV3(const objl::Vector3 a, const objl::Vector3 b)
{
	return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

// Angle between 2 Vector3 Objects
float objl::math::AngleBetweenV3(const objl::Vector3 a, const objl::Vector3 b)
{
	float angle = DotV3(a, b);
	angle /= (MagnitudeV3(a) * MagnitudeV3(b));
	return angle = acosf(angle);
}

objl::Vector3 objl::algorithm::operator*(const float& left, const objl::Vector3& right)
{
	return objl::Vector3(right.X * left, right.Y * left, right.Z * left);
}

// Check to see if a Vector3 Point is within a 3 Vector3 Triangle
bool objl::algorithm::inTriangle(objl::Vector3 point, objl::Vector3 tri1, objl::Vector3 tri2, objl::Vector3 tri3)
{
	// Starting vars
	objl::Vector3 u = tri2 - tri1;
	objl::Vector3 v = tri3 - tri1;
	objl::Vector3 w = point - tri1;
	objl::Vector3 n = objl::math::CrossV3(u, v);

	float y = (objl::math::DotV3(objl::math::CrossV3(u, w), n) / objl::math::DotV3(n, n));
	float b = (objl::math::DotV3(objl::math::CrossV3(u, w), n) / objl::math::DotV3(n, n));
	float a = 1 - y - b;

	// Projected point
	objl::Vector3  p = (a * tri1) + (b * tri2) + (y * tri3);

	if (a >= 0 && a <= 1
		&& b >= 0 && b <= 1
		&& y >= 0 && y <= 1)
	{
		return true;
	}
	else
		return false;
}

		