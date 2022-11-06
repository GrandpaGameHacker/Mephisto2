#pragma once
#include "Vector.inl"
#include <cmath>
#include <memory.h>
template <typename T>
class Mat44
{
public:
	Mat44()
	{
		memset(&M, 0, sizeof(T) * 16);
	}

	Mat44(Mat44& matrix)
	{
		memcpy(&M, &matrix, sizeof(T) * 16);
	}

	Mat44(const Vec4<T>& InX, const Vec4<T>& InY, const Vec4<T>& InZ, const Vec4<T>& InW)
	{
		M[0][0] = InX.X;
		M[0][1] = InX.Y;
		M[0][2] = InX.Z;
		M[0][3] = InX.W;

		M[1][0] = InY.X;
		M[1][1] = InY.Y;
		M[1][2] = InY.Z;
		M[1][3] = InY.W;

		M[2][0] = InZ.X;
		M[2][1] = InZ.Y;
		M[2][2] = InZ.Z;
		M[2][3] = InZ.W;

		M[3][0] = InW.X;
		M[3][1] = InW.Y;
		M[3][2] = InW.Z;
		M[3][3] = InW.W;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	Mat44(const Vec3<T1>& InX, const Vec3<T2>& InY, const Vec3<T3>& InZ, const Vec3<T4>& InW)
	{
		M[0][0] = (T)InX.X;
		M[0][1] = (T)InX.Y;
		M[0][2] = (T)InX.Z;
		M[0][3] = (T)InX.W;

		M[1][0] = (T)InY.X;
		M[1][1] = (T)InY.Y;
		M[1][2] = (T)InY.Z;
		M[1][3] = (T)InY.W;

		M[2][0] = (T)InZ.X;
		M[2][1] = (T)InZ.Y;
		M[2][2] = (T)InZ.Z;
		M[2][3] = (T)InZ.W;

		M[3][0] = (T)InW.X;
		M[3][1] = (T)InW.Y;
		M[3][2] = (T)InW.Z;
		M[3][3] = (T)InW.W;
	}


	static Mat44<T> Translate(const Mat44<T>& Matrix, const Vec3<T>& Translation)
	{
		Mat44<T> RetMatrix = Matrix;
		const Vec4<T>& C1 = *(const Vec4<T>*) & Matrix.M[0][0];
		const Vec4<T>& C2 = *(const Vec4<T>*) & Matrix.M[1][0];
		const Vec4<T>& C3 = *(const Vec4<T>*) & Matrix.M[2][0];
		const Vec4<T>& C4 = *(const Vec4<T>*) & Matrix.M[3][0];
		Vec4<T>& OC3 = *(Vec4<T>*) & RetMatrix.M[3];
		OC3 = C1 * Translation.X + C2 * Translation.Y + C3 * Translation.Z + C4;
		return RetMatrix;
	}

	static Mat44<T> Scale(const Mat44<T>& Matrix, const Vec3<T>& Scale)
	{
		Mat44<T> RetMatrix = Matrix;
		const Vec3<T>& C0 = *(const Vec3<T>*) & Matrix.M[0][0];
		const Vec3<T>& C1 = *(const Vec3<T>*) & Matrix.M[1][0];
		const Vec3<T>& C2 = *(const Vec3<T>*) & Matrix.M[2][0];
		const Vec3<T>& C3 = *(const Vec3<T>*) & Matrix.M[3][0];

		Vec3<T>& OC0 = *(Vec3<T>*) & RetMatrix.M[0][0];
		Vec3<T>& OC1 = *(Vec3<T>*) & RetMatrix.M[1][0];
		Vec3<T>& OC2 = *(Vec3<T>*) & RetMatrix.M[2][0];
		Vec3<T>& OC3 = *(Vec3<T>*) & RetMatrix.M[3][0];

		OC0 = C0 * Scale.X;
		OC1 = C1 * Scale.Y;
		OC2 = C2 * Scale.Z;
		OC3 = C3;

		return RetMatrix;
	}

	static Mat44<T>	Perspective(T Fov, T Aspect, T Near, T Far)
	{
		Mat44<T> RetMatrix = Mat44<T>::Identity;

		T FrustumDepth = Far - Near;
		T OneOverDepth = T(1.0) / FrustumDepth;
		bool bLeftHanded = false;

		RetMatrix.M[1][1] = T(1.0) / std::tan(T(0.5) * Fov);
		RetMatrix.M[0][0] = (bLeftHanded ? T(1.0) : T(-1.0)) * RetMatrix.M[1][1] / Aspect;
		RetMatrix.M[2][2] = Far * OneOverDepth;
		RetMatrix.M[3][2] = (-Far * Near) * OneOverDepth;
		RetMatrix.M[2][3] = 1;
		RetMatrix.M[3][3] = 0;

		return RetMatrix;
	}
	T M[4][4];
	static const Mat44<T> Identity;
};