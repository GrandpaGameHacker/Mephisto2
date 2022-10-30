#pragma once
template <typename T>
struct Vec2
{
	Vec2() :
		X(0), Y(0)
	{
	}

	Vec2(T x, T y) :
		X(x), Y(y)
	{
	}

	T X, Y;
};

template <typename T>
struct Vec3
{
	Vec3() :
		X(0), Y(0), Z(0)
	{
	}

	Vec3(T x, T y, T z) :
		X(x), Y(y), Z(z)
	{
	}

	T X, Y, Z;
};

template <typename T>
struct Vec4
{
	Vec4() :
		X(0), Y(0), Z(0), W(0)
	{
	}

	Vec4(T x, T y, T z, T w) :
		X(x), Y(y), Z(z), W(w)
	{
	}
	T X, Y, Z, W;
};