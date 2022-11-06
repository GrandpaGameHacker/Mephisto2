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

	template <typename Cast>
	Vec2(Vec2<Cast> arg)
	{
		X = (Cast) arg.X;
		Y = (Cast) arg.Y;
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

	template <typename Cast>
	Vec3(Vec3<Cast> arg)
	{
		X = (Cast) arg.X;
		Y = (Cast) arg.Y;
		Z = (Cast) arg.Z;
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

	template <typename Cast>
	Vec4(Vec4<Cast> arg)
	{
		X = (Cast) arg.X;
		Y = (Cast) arg.Y;
		Z = (Cast) arg.Z;
		W = (Cast) arg.W;
	}



	T X, Y, Z, W;
};