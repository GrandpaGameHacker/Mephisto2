#include "Noise.h"
#include "NoiseConstants.h"
#include "Types.h"
#pragma warning(disable:4244)
namespace
{
	using namespace ME::Math;
};

Noise::Noise()
{

}

NoiseState& Noise::GetState()
{
	return State;
}

NoiseSettings& Noise::GetSettings()
{
	return Config;
}

void Noise::SetBasicType(ENoiseType Type)
{
	Config.NoiseType = Type;
}

void Noise::SetRotation3DType(ERotation3DType Type)
{
	Config.Rotation3DType = Type;
}

void Noise::SetFractalType(EFractalType Type)
{
	Config.FractalType = Type;
}

void Noise::SetDomainWarpType(EDomainWarpType Type)
{
	Config.DomainWarpType = Type;
}

void Noise::SetCellularDistanceFunction(ECellularDistanceFunction Function)
{
	Config.CellularDistanceFunc = Function;
}

void Noise::SetCellularReturnType(ECellularReturnType ReturnType)
{
	Config.CellularReturnType = ReturnType;
}

void Noise::SetSeed(int seed)
{
	State.Seed = seed;
}

void Noise::SetFrequency(float frequency)
{
	State.Frequency = frequency;
}

void Noise::FractalSetOctave(int octave)
{
	State.Octaves = octave;
}

void Noise::FractalSetLacunarity(float lacunarity)
{
	State.Lacunarity = lacunarity;
}

void Noise::FractalSetGain(float gain)
{
	State.Gain = gain;
}

void Noise::FractalSetWeightedStrength(float strength)
{
	State.WeightedStrength = strength;
}

void Noise::FractalSetPingPongStrength(float strength)
{
	State.PingPongStrength = strength;
}

void Noise::CellularSetJitter(float jitterAmount)
{
	State.CellularJitterModifier = jitterAmount;
}

void Noise::DomainWarpSetAmplitude(float amplitude)
{
	State.DomainWarpAmplitude = amplitude;
}

float Noise::GetNoise2D(Vec2<float>& v)
{
	switch (Config.NoiseType)
	{
	case ENoiseType::OpenSimplex2:
		return Simplex2D(v);
		break;
	case ENoiseType::OpenSimplex2S:
		return OpenSimplex2S_2D(v);
		break;
	case ENoiseType::Perlin:
		return Perlin2D(v);
		break;
	case ENoiseType::Value:
		return Value2D(v);
		break;
	case ENoiseType::ValueCubic:
		return ValueCubic2D(v);
		break;
	case ENoiseType::Cellular:
		return Cellular2D(v);
		break;
	}
	return 0.f;
}

float Noise::GetNoise3D(Vec3<float>& v)
{
	switch (Config.NoiseType)
	{
	case ENoiseType::OpenSimplex2:
		return OpenSimplex2_3D(v);
		break;
	case ENoiseType::OpenSimplex2S:
		return OpenSimplex2S_3D(v);
		break;
	case ENoiseType::Perlin:
		return Perlin3D(v);
		break;
	case ENoiseType::Value:
		return Value3D(v);
		break;
	case ENoiseType::ValueCubic:
		return ValueCubic3D(v);
		break;
	case ENoiseType::Cellular:
		return Cellular3D(v);
		break;
	}
	return 0.f;
}

void Noise::DomainWarp2D(Vec2<float>& v)
{
	switch (Config.FractalType)
	{
	default:
		//DomainWarpSingle2D(v);
		break;
	case EFractalType::DomainWarpProgressive:
		//DomainWarpFractalProgressive2D(v);
		break;
	case EFractalType::DomainWarpIndependent:
		//DomainWarpFractalIndependent2D(v);
		break;
	}
}


void Noise::DomainWarp3D(Vec3<float>& v)
{
	switch (Config.FractalType)
	{
	default:
		DomainWarpSingle3D(v);
		break;
	case EFractalType::DomainWarpProgressive:
		DomainWarpFractalProgressive3D(v);
		break;
	case EFractalType::DomainWarpIndependent:
		DomainWarpFractalIndependent3D(v);
		break;
	}
}

float Noise::FastMin(const Vec2<float>& vIn)
{
	return vIn.X < vIn.Y ? vIn.X : vIn.Y;
}

float Noise::FastMax(const Vec2<float>& vIn)
{
	return vIn.X > vIn.Y ? vIn.X : vIn.Y;
}

float Noise::FastAbs(float fIn)
{
	return fIn < 0 ? -fIn : fIn;
}

union FConversionUnion
{
	float a;
	int32 b;
};

float Noise::CastInt2Float(int in)
{
	FConversionUnion FUnion;
	FUnion.b = in;
	return FUnion.a;
}

int Noise::CastFloat2Int(float in)
{
	FConversionUnion FUnion;
	FUnion.a = in;
	return FUnion.b;
}

float Noise::InverseSquareRoot(float in)
{
	float half = 0.5f * in;
	in = CastFloat2Int(Constants::InverseSquareConst - (CastFloat2Int(in) >> 1));
	in = in * (1.5f - half * in * in);
	return in;
}

float Noise::FastSquareRoot(float in)
{
	return in * InverseSquareRoot(in);
}

float Noise::FastFloor(float in)
{
	return (in >= 0 ? (int)in : (int)in - 1);
}

Vec2<float> Noise::FastFloor(Vec2<float> in)
{
	in.X = (in.X >= 0 ? (int)in.X : (int)in.X - 1);
	in.Y = (in.X >= 0 ? (int)in.X : (int)in.X - 1);
	return in;
}

Vec3<float> Noise::FastFloor(Vec3<float> in)
{
	in.X = (in.X >= 0 ? (int)in.X : (int)in.X - 1);
	in.Y = (in.X >= 0 ? (int)in.X : (int)in.X - 1);
	in.Z = (in.Z >= 0 ? (int)in.Z : (int)in.Z - 1);
	return in;
}

float Noise::FastRound(float in)
{
	return in >= 0 ? (int)(in + 0.5f) : (int)(in - 0.5f);
}

Vec2<float> Noise::FastRound(Vec2<float> in)
{
	in.X = in.X >= 0 ? (int)(in.X + 0.5f) : (int)(in.X - 0.5f);
	in.Y = in.Y >= 0 ? (int)(in.Y + 0.5f) : (int)(in.Y- 0.5f);
	return in;
}
Vec3<float> Noise::FastRound(Vec3<float> in)
{
	in.X = in.X >= 0 ? (int)(in.X + 0.5f) : (int)(in.X - 0.5f);
	in.Y = in.Y >= 0 ? (int)(in.Y + 0.5f) : (int)(in.Y - 0.5f);
	in.Z = in.Z >= 0 ? (int)(in.Z + 0.5f) : (int)(in.Z - 0.5f);
	return in;
}

float Noise::Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float Noise::CubicLerp(float a, float b, float c, float d, float t)
{
	float p = (d - c) - (a - b);
	return t * t * t * p + t * t * ((a - b) - p) + t * (c - a) + b;
}

float Noise::InterpolateHermite(float t)
{
	return t * t * (3 - 2 * t);
}

float Noise::InterpolateQuintic(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float Noise::PingPong(float t)
{
	t -= (int)(t * 0.5f) * 2;
	return t < 1 ? t : 2 - t;
}

float Noise::CalculateFractalBounding()
{
	float gain = FastAbs(State.Gain);
	float amplifier = gain;
	float amplifierFractal = 1.0f;
	for (int i = 1; i < State.Octaves; i++)
	{
		amplifierFractal += amplifier;
		amplifier *= gain;
	}
	return 1.0f / amplifierFractal;
}

int Noise::Hash2D(Vec2<int> vPrimed)
{
	int Hash = State.Seed ^ vPrimed.X ^ vPrimed.Y;
	Hash *= Constants::HashConst;
	return Hash;
}

int Noise::Hash3D(Vec3<int> vPrimed)
{
	int Hash = State.Seed ^ vPrimed.X ^ vPrimed.Y ^ vPrimed.Z;
	Hash *= Constants::HashConst;
	return Hash;
}

float Noise::ValueCoordinate2D(Vec2<int> vPrimed)
{
	int Hash = Hash2D(vPrimed);
	Hash *= Hash;
	Hash ^= Hash << 19;
	return Hash * (1 / Constants::HashFloatConst);
}

float Noise::ValueCoordinate2D(Vec3<int> vPrimed)
{
	int Hash = Hash3D(vPrimed);
	Hash *= Hash;
	Hash ^= Hash << 19;
	return Hash * (1 / Constants::HashFloatConst);
}

float Noise::GradientCoordinate2D(Vec2<int> vPrimed, Vec2<float> vIn)
{
	int Hash = Hash2D(vPrimed);
	Hash ^= Hash >> 15;
	Hash &= 127 << 1;
	return vIn.X * Constants::Gradients2D[Hash]
		+ vIn.Y * Constants::Gradients2D[Hash | 1];
}

float Noise::GradientCoordinate3D(Vec3<int> vPrimed, Vec3<float> vIn)
{
	int Hash = Hash3D(vPrimed);
	Hash ^= Hash >> 15;
	Hash &= 127 << 1;
	return vIn.X * Constants::Gradients3D[Hash]
		+ vIn.Y * Constants::Gradients3D[Hash | 1]
		+ vIn.Z * Constants::Gradients3D[Hash | 2];
}

void Noise::GradientCoordinateOutput2D(Vec2<int> vPrimed, Vec2<float>& vOut)
{
	int Hash = Hash2D(vPrimed) & (255 << 1);

	vOut.X = Constants::RandVecs2D[Hash];
	vOut.Y = Constants::RandVecs2D[Hash | 1];
}

void Noise::GradientCoordinateOutput3D(Vec3<int> vPrimed, Vec3<float>& vOut)
{
	int Hash = Hash3D(vPrimed) & (255 << 1);

	vOut.X = Constants::RandVecs2D[Hash];
	vOut.Y = Constants::RandVecs2D[Hash | 1];
	vOut.Z = Constants::RandVecs2D[Hash | 2];
}

void Noise::GradientCoordinateDual2D(Vec2<int> vPrimed, Vec2<float> vIn, Vec2<float>& vOut)
{
	int Hash = Hash2D(vPrimed);
	int idx1 = Hash & (127 << 1);
	int idx2 = (Hash >> 7) & (255 << 1);
	
	Vec2<float> g = Vec2<float>(
		Constants::Gradients2D[idx1],
		Constants::Gradients2D[idx1 | 1]);
	float value = vIn.X * g.X + vIn.Y * g.Y;

	Vec2<float> go = Vec2<float>(
		Constants::Gradients2D[idx2],
		Constants::Gradients2D[idx2 | 1]);
	
	vOut.X = value * go.X;
	vOut.Y = value * go.Y;
}

void Noise::GradientCoordinateDual3D(Vec3<int> vPrimed, Vec3<float> vIn, Vec3<float>& vOut)
{
	int Hash = Hash3D(vPrimed);
	int idx1 = Hash & (127 << 1);
	int idx2 = (Hash >> 7) & (255 << 1);

	Vec3<float> g = Vec3<float>(
		Constants::Gradients3D[idx1],
		Constants::Gradients3D[idx1 | 1],
		Constants::Gradients3D[idx1 | 2]
		);
	float value = vIn.X * g.X + vIn.Y * g.Y + vIn.Z * g.Z;

	Vec3<float> go = Vec3<float>(
		Constants::Gradients3D[idx2],
		Constants::Gradients3D[idx2 | 1],
		Constants::Gradients3D[idx2 | 2]
		);

	vOut.X = value * go.X;
	vOut.Y = value * go.Y;
	vOut.Z = value * go.Z;
}

float Noise::Simplex2D(Vec2<float> v)
{
	auto ij = FastFloor(v);
	auto vi = Vec2<float>((float)(v.X - ij.X), (float)(v.Y - ij.Y));

	float t = (vi.X + vi.Y) * Constants::G2;
	auto v0 = Vec2<float>((float)(vi.X - t), (float)(vi.Y - t));

	ij.X *= Constants::PrimeX;
	ij.Y *= Constants::PrimeY;

	float n0, n1, n2;
	float a = 0.5f - v0.X * v0.X - v0.Y * v0.Y;
	if (a <= 0)
	{
		n0 = 0;
	}
	else
	{
		n0 = (a * a) * (a * a) * GradientCoordinate2D(ij, v0);
	}

	float c = (float)(2 * (1 - 2 * Constants::G2) * (1 / Constants::G2 - 2)) * t +
			((float)(-2 * (1 - 2 * Constants::G2) * (1 - 2 * Constants::G2)) + a);
	if (c < 0)
	{
		n2 = 0;
	}
	else
	{
		auto v2 = Vec2<float>(v0.X + (2*(float)Constants::G2-1),
							  v0.Y + (2 * (float)Constants::G2 - 1));
		auto temp = ij;
		temp.X = temp.X + Constants::PrimeX;
		temp.Y = temp.Y + Constants::PrimeY;
		n2 = (c * c) * (c * c) * GradientCoordinate2D(temp, v2);
	}

	if (v0.Y > v0.X)
	{
		auto v1 = Vec2<float>((v0.X + (float)Constants::G2),
			(v0.Y + ((float)Constants::G2 - 1)));
		float b = 0.5f - v1.X * v1.X - v1.Y * v1.Y;
		if (b <= 0)
		{
			n1 = 0;
		}
		else
		{
			auto temp = ij;
			temp.Y = temp.Y + Constants::PrimeY;
			n1 = (b * b) * (b * b) * GradientCoordinate2D(temp, v1);
		}
	}
	else
	{
		auto v1 = Vec2<float>(v0.X + ((float)Constants::G2 - 1),
							 (v0.Y + (float)Constants::G2));
		float b = 0.5f - v1.X * v1.X - v1.Y * v1.Y;
		if (b <= 0)
		{
			n1 = 0;
		}
		else
		{
			auto temp = ij;
			temp.Y = temp.Y + Constants::PrimeY;
			n1 = (b * b) * (b * b) * GradientCoordinate2D(temp, v1);
		}
	}

	return (n0 + n1 + n2) * Constants::Simplex2DFinalMultiplier;
}

float Noise::OpenSimplex2_3D(Vec3<float> v)
{
	auto ijk = Vec3<int>(FastRound(v.X), FastRound(v.Y), FastRound(v.Z));
	auto v0 = Vec3<float>
		((float)(v.X - ijk.X),
		(float)(v.Y - ijk.Y),
		(float)(v.Z - ijk.Z));

	auto NSign = Vec3<int>
		((int)(-1.0f - v0.X) | 1,
		(int)(-1.0f - v0.Y) | 1,
		(int)(-1.0f - v0.Z) | 1);

	auto a0 = Vec3<int>
			(NSign.X * -v0.X,
			NSign.Y * -v0.Y,
			NSign.Z * -v0.Z);

	ijk.X *= Constants::PrimeX;
	ijk.Y *= Constants::PrimeY;
	ijk.Z *= Constants::PrimeZ;

	float value = 0;
	float a = (0.6f - v0.X * v0.X) - (v0.Y * v0.Y + v0.Z * v0.Z);
	for (int l = 0; true; l++)
	{
		if (a > 0)
		{
			value += (a * a) * (a * a) * GradientCoordinate3D(ijk, v0);
		}

		float b = a + 1;
		auto ijk1 = ijk;
		auto v1 = v0;

		if (a0.X >= a0.Y && a0.X >= a0.Z)
		{
			v1.X += NSign.X;
			b -= NSign.X * 2 * v1.X;
			ijk1.X -= NSign.X * Constants::PrimeX;
		}
		else if (a0.Y > a0.X && a0.Y > a0.Z)
		{
			v1.Y += NSign.Y;
			b -= NSign.Y * 2 * v1.Y;
			ijk1.Y -= NSign.Y * Constants::PrimeY;
		}
		else
		{
			v1.Z += NSign.Z;
			b -= NSign.Z * 2 * v1.Z;
			ijk.Z -= NSign.Z * Constants::PrimeZ;
		}

		if (b > 0)
		{
			value += (b * b) * (b * b) * GradientCoordinate3D(ijk1, v1);
		}

		if (l = 1) break;

		a0.X = 0.5f - a0.X;
		a0.Y = 0.5f - a0.Y;
		a0.Z = 0.5f - a0.Z;

		v0.X = NSign.X * a0.X;
		v0.Y = NSign.Y * a0.Y;
		v0.Z = NSign.Z * a0.Z;

		a += (0.75f - a0.X) - (a0.Y + a0.Z);

		ijk.X += (NSign.X >> 1) & Constants::PrimeX;
		ijk.Y += (NSign.Y >> 1) & Constants::PrimeY;
		ijk.Z += (NSign.Z >> 1) & Constants::PrimeZ;

		State.Seed = ~State.Seed;
	}
	return value * Constants::Simplex2_3DFinalMultiplier;
}

float Noise::OpenSimplex2S_2D(Vec2<float> v)
{
	auto ij = FastFloor(v);
	auto vi = Vec2<float>((float)(v.X - ij.X), (float)(v.Y - ij.Y));
	
	ij.X *= Constants::PrimeX;
	ij.Y *= Constants::PrimeY;

	auto ij1 = Vec2<int>(ij.X + Constants::PrimeX, ij.Y + Constants::PrimeY);
	
	float t = (vi.X + vi.Y) * (float)Constants::G2;
	auto v0 = Vec2<float>(vi.X - t, vi.Y - t);
	float a0 = (2.0f / 3.0f) - v0.X * v0.X - v0.Y * v0.Y;

	float value = (a0 * a0) * (a0 * a0) * GradientCoordinate2D(ij, v0);

	float a1 =	(float)(2 * (1 - 2 * Constants::G2) *
				(1 / Constants::G2 - 2)) * t +
				((float)(-2 * (1 - 2 * Constants::G2)) + a0);

	auto v1 = Vec2<float>
		(v0.X - (float)(1 - 2 * Constants::G2),
	     v0.Y - (float)(1 - 2 * Constants::G2));

	value += (a1 * a1) * (a1 * a1) * GradientCoordinate2D(ij, v1);

	float vxmvy = vi.X - vi.Y;
	if (t > Constants::G2)
	{
		if (vi.X + vxmvy > 1)
		{
			auto v2 = Vec2<float>
				(v0.X + (float)(3 * Constants::G2 - 2),
				v0.Y + (float)(3 * Constants::G2 - 1));
			float a2 = (2.0f / 3.0f) - v2.X * v2.X - v2.Y * v2.Y;
			if (a2 > 0)
			{
				auto temp = ij;
				temp.X += (Constants::PrimeX << 1);
				temp.Y += Constants::PrimeY;
				value += (a2 * a2) * (a2 * a2) * GradientCoordinate2D(temp, v2);
			}
		}
		else
		{
			auto v2 = Vec2<float>
				(v0.X + (float)(Constants::G2),
					v0.Y + (float)(Constants::G2 - 1));
			float a2 = (2.0f / 3.0f) - v2.X * v2.X - v2.Y * v2.Y;
			if (a2 > 0)
			{
				auto temp = ij;
				temp.Y += Constants::PrimeY;
				value += (a2 * a2) * (a2 * a2) * GradientCoordinate2D(temp, v2);
			}
		}

		if (vi.Y - vxmvy > 1)
		{
			auto v3 = Vec2<float>
				(v0.X + (float)(3 * Constants::G2 - 1),
					v0.Y + (float)(3 * Constants::G2 - 2));
			float a3 = (2.0f / 3.0f) - v3.X * v3.X - v3.Y * v3.Y;
			if (a3 > 0)
			{
				auto temp = ij;
				temp.X += Constants::PrimeX;
				temp.Y += (Constants::PrimeY << 1);
				value += (a3 * a3) * (a3 * a3) * GradientCoordinate2D(temp, v3);
			}
		}
		else
		{
			auto v3 = Vec2<float>
				(v0.X + (float)(Constants::G2 - 1),
					v0.Y + (float)(Constants::G2 ));
			float a3 = (2.0f / 3.0f) - v3.X * v3.X - v3.Y * v3.Y;
			if (a3 > 0)
			{
				auto temp = ij;
				temp.X += Constants::PrimeX;
				value += (a3 * a3) * (a3 * a3) * GradientCoordinate2D(temp, v3);
			}
		}
	}
	else
	{
		if (vi.X + vxmvy < 0)
		{
			auto v2 = Vec2<float>
				(v0.X + (float)(1 - Constants::G2),
					v0.Y + (float)(Constants::G2));
			float a2 = (2.0f / 3.0f) - v2.X * v2.X - v2.Y * v2.Y;
			if (a2 > 0)
			{
				auto temp = ij;
				temp.X -= Constants::PrimeX;
				value += (a2 * a2) * (a2 * a2) * GradientCoordinate2D(temp, v2);
			}
		}
		else
		{
			auto v2 = Vec2<float>
				(v0.X + (float)(Constants::G2 - 1),
					v0.Y + (float)(Constants::G2));
			float a2 = (2.0f / 3.0f) - v2.X * v2.X - v2.Y * v2.Y;
			if (a2 > 0)
			{
				auto temp = ij;
				temp.X += Constants::PrimeX;
				value += (a2 * a2) * (a2 * a2) * GradientCoordinate2D(temp, v2);
			}
		}

		if (vi.Y - vxmvy > 1)
		{
			auto v3 = Vec2<float>
				(v0.X + (float)(Constants::G2),
					v0.Y + (float)(Constants::G2 - 1));
			float a2 = (2.0f / 3.0f) - v3.X * v3.X - v3.Y * v3.Y;
			if (a2 > 0)
			{
				auto temp = ij;
				temp.Y -= Constants::PrimeY;
				value += (a2 * a2) * (a2 * a2) * GradientCoordinate2D(temp, v3);
			}
		}
		else
		{
			auto v3 = Vec2<float>
				(v0.X + (float)(Constants::G2),
					v0.Y + (float)(Constants::G2 - 1));
			float a2 = (2.0f / 3.0f) - v3.X * v3.X - v3.Y * v3.Y;
			if (a2 > 0)
			{
				auto temp = ij;
				temp.Y += Constants::PrimeY;
				value += (a2 * a2) * (a2 * a2) * GradientCoordinate2D(temp, v3);
			}
		}
	}
	return value * Constants::OpenSimplex2S_2DFinalMultiplier;
}

float Noise::OpenSimplex2S_3D(Vec3<float> v)
{
	Vec3<int> ijk = FastFloor(v);

	auto vi = Vec3<float>(
		(float)(v.X - ijk.X),
		(float)(v.Y - ijk.Y),
		(float)(v.Z - ijk.Z));

	ijk = Vec3<int>(
		vi.X * Constants::PrimeX,
		vi.Z * Constants::PrimeY,
		vi.Z * Constants::PrimeZ);

	int SeedOriginal = State.Seed;
	int Seed0 = SeedOriginal + 1293373;

	auto NMask = Vec3(
		(int)(-0.5f - vi.X),
		(int)(-0.5f - vi.Y),
		(int)(-0.5f - vi.Z));

	auto v0 = Vec3<float>(
		vi.X + NMask.X,
		vi.Y + NMask.Y,
		vi.Z + NMask.Z);

	float a0 = 0.75f - v0.X * v0.X - v0.Y * v0.Y - v0.Z * v0.Z;

	auto temp = Vec3<int>(
		ijk.X + (NMask.X & Constants::PrimeX),
		ijk.Y + (NMask.Y & Constants::PrimeY),
		ijk.Z + (NMask.Z & Constants::PrimeZ));
	State.Seed = SeedOriginal;
	float value = (a0 * a0) * (a0 * a0) * GradientCoordinate3D(temp, v0);

	auto v1 = Vec3<float>(
		vi.X - 0.5f,
		vi.Y - 0.5f,
		vi.Z - 0.5f
		);

	float a1 = 0.75f - v1.X * v1.X - v1.Y * v1.Y - v1.Z * v1.Z;
	temp = Vec3<int>(
		ijk.X + Constants::PrimeX,
		ijk.Y + Constants::PrimeY,
		ijk.Z + Constants::PrimeZ);
	State.Seed = Seed0;
	value += (a1 * a1) * (a1 * a1) * GradientCoordinate3D(temp, v1);

	Vec3<float> AFlipMask0;
	Vec3<float> AFlipMask1;

	AFlipMask0.X = ((NMask.X | 1) << 1) * v1.X;
	AFlipMask0.Y= ((NMask.Y | 1) << 1) * v1.Y;
	AFlipMask0.Z = ((NMask.Z | 1) << 1) * v1.Z;
	AFlipMask1.X = (-2 - (NMask.X << 2)) * v1.X - 1.0f;
	AFlipMask1.Y = (-2 - (NMask.Y << 2)) * v1.Y - 1.0f;
	AFlipMask1.Z = (-2 - (NMask.Z << 2)) * v1.Z - 1.0f;

	bool skip5 = false;
	float a2 = AFlipMask0.Z + a0;
	if (a2 > 0)
	{
		temp = Vec3<int>(
			ijk.X + (~NMask.X & Constants::PrimeX),
			ijk.Y + (NMask.Y & Constants::PrimeY),
			ijk.Z + (NMask.Z & Constants::PrimeZ));

			auto v2 = Vec3<float>(
				v0.X - (NMask.X | 1),
				v0.Y,
				v0.Z);

		State.Seed = SeedOriginal;
		value += (a2 * a2) * (a2 * a2) * GradientCoordinate3D(temp, v2);
	}
	else
	{
		float a3 = AFlipMask0.Y + AFlipMask0.Z + a0;
		if (a3 > 0)
		{
			auto v3 = Vec3<float>(
				v0.X,
				v0.Y + (NMask.Y | 1),
				v0.Z + (NMask.Z | 1));

			temp = Vec3<int>(
				ijk.X + (NMask.X & Constants::PrimeX),
				ijk.Y + (~NMask.Y & Constants::PrimeY),
				ijk.Z + (~NMask.Z & Constants::PrimeZ));

			value += (a3 * a3) * (a3 * a3) * GradientCoordinate3D(temp, v3);
		}

		float a4 = AFlipMask1.X + a1;
		if (a4 > 0)
		{
			auto v4 = Vec3<float>(
				(NMask.X | 1) + v1.X,
				v1.Y,
				v1.Z);

			temp = Vec3<int>(
				ijk.X + (NMask.X & (Constants::PrimeX* 2)),
				ijk.Y + Constants::PrimeY,
				ijk.Z + Constants::PrimeZ);

			State.Seed = Seed0;
			value += (a4 * a4) * (a4 * a4) * GradientCoordinate3D(temp, v4);
			skip5 = true;
		}
	}

	bool skip9 = false;
	float a6 = AFlipMask0.Y + a0;
	if (a6 > 0)
	{
		auto v6 = Vec3<float>(
			v0.X,
			v0.Y - (NMask.Y | 1),
			v0.Z);

		temp = Vec3<int>(
			ijk.X + (NMask.X & Constants::PrimeX),
			ijk.Y + (~NMask.Y & Constants::PrimeY),
			ijk.Z + (NMask.Y & Constants::PrimeZ));

		State.Seed = SeedOriginal;
		value += (a6 * a6) * (a6 * a6) * GradientCoordinate3D(temp, v6);
	}
	else
	{
		float a7 = AFlipMask0.X + AFlipMask0.Z + a0;
		if (a7 > 0)
		{
			auto v7 = Vec3<float>(
				v0.X - (NMask.X | 1),
				v0.Y,
				v0.Z - (NMask.Z | 1));

			temp = Vec3<int>(ijk.X + (~NMask.X & Constants::PrimeX),
				ijk.Y + (NMask.Y & Constants::PrimeY),
				ijk.Z + (~NMask.Z & Constants::PrimeZ));

			State.Seed = SeedOriginal;
			value += (a7 * a7) * (a7 * a7) * GradientCoordinate3D(temp, v7);
		}

		float a8 = AFlipMask1.Y + a1;
		if (a8 > 0)
		{
			auto v8 = Vec3<float>(
				v1.X,
				(NMask.Y | 1) + v1.Y,
				v1.Z);

			temp = Vec3<int>(
				ijk.X + Constants::PrimeX,
				ijk.Y + (NMask.Y & (Constants::PrimeY << 1)),
				ijk.Z + Constants::PrimeZ);

			State.Seed = Seed0;
			value += (a8 * a8) * (a8 * a8) * GradientCoordinate3D(temp, v8);
			skip9 = true;
		}
	}

	bool skipD = false;
	float aA = AFlipMask0.Z + a0;
	if (aA > 0)
	{
		auto vA = Vec3<float>(
			v0.X,
			v0.Y,
			v0.Z - (NMask.Z | 1));

		temp = Vec3<int>(
			ijk.X + (NMask.X & Constants::PrimeX),
			ijk.Y + (NMask.Y & Constants::PrimeY),
			ijk.Z + (~NMask.Z & Constants::PrimeZ));

		State.Seed = SeedOriginal;
		value += (aA * aA) * (aA * aA) * GradientCoordinate3D(temp, vA);
	}
	else
	{
		float aB = AFlipMask0.X + AFlipMask0.Y + a0;
		if (aB > 0)
		{
			auto vB = Vec3<float>(
				v0.X - (NMask.X | 1),
				v0.Y - (NMask.Y | 1),
				v0.Z - v0.Z);

			temp = Vec3<int>(
				ijk.X + (~NMask.X & Constants::PrimeX),
				ijk.Y + (~NMask.Y & Constants::PrimeY),
				ijk.Z + (NMask.Z & Constants::PrimeZ));

			State.Seed = SeedOriginal;
			value += (aB * aB) * (aB * aB) * GradientCoordinate3D(temp, vB);
		}

		float aC = AFlipMask1.Z + a1;
		if (aC > 0)
		{
			auto vC = Vec3<float>(
				v1.X,
				v1.Y,
				v1.Z);

			temp = Vec3<int>(
				ijk.X + Constants::PrimeX,
				ijk.Y + Constants::PrimeY,
				ijk.Z + (NMask.Z & (Constants::PrimeZ << 1)));

			State.Seed = Seed0;
			value += (aC * aC) * (aC * aC) * GradientCoordinate3D(temp, vC);
			skipD = true;
		}
	}

	if (!skip5)
	{
		float a5 = AFlipMask1.Y + AFlipMask1.Z + a1;
		if (a5 > 0)
		{
			auto v5 = Vec3<float>(
				v1.X,
				(NMask.Y | 1) + v1.Y,
				(NMask.Z | 1) + v1.Z);

			temp = Vec3<int>(
				ijk.X + Constants::PrimeX,
				ijk.Y + (NMask.Y & (Constants::PrimeY << 1)),
				ijk.Z + (NMask.Z & (Constants::PrimeZ << 1)));

			State.Seed = Seed0;
			value += (a5 * a5) * (a5 * a5) * GradientCoordinate3D(temp, v5);
		}
	}

	if (!skip9)
	{
		float a9 = AFlipMask1.X + AFlipMask1.Z + a1;
		if (a9 > 0)
		{
			auto v9 = Vec3<float>(
				(NMask.X | 1) + v1.X,
				v1.Y,
				(NMask.Z | 1) + v1.Z);

			temp = Vec3<int>(
				ijk.X + (NMask.X & (Constants::PrimeX * 2)),
				ijk.Y + Constants::PrimeY,
				ijk.Z + (NMask.Z & (Constants::PrimeZ << 1)));
			
			State.Seed = Seed0;
			value += (a9 * a9) * (a9 * a9) * GradientCoordinate3D(temp, v9);
		}
	}

	if (!skipD)
	{
		float aD = AFlipMask1.X + AFlipMask1.Y + a1;
		if (aD > 0)
		{

			auto vD = Vec3<float>(
				(NMask.X | 1) + v1.X,
				(NMask.Y | 1) + v1.Y,
				v1.Z);

			temp = Vec3<int>(
				ijk.X + (NMask.X & (Constants::PrimeX << 1)),
				ijk.Y + (NMask.Y & (Constants::PrimeY << 1)),
				ijk.Z + Constants::PrimeZ);

			State.Seed = Seed0;
			value += (aD * aD) * (aD * aD) * GradientCoordinate3D(temp, vD);
		}
	}
	State.Seed = SeedOriginal;
	return value * Constants::OpenSimplex2S_3DFinalMultiplier;
}

float Noise::Cellular2D(Vec2<float> v)
{
	auto vr = FastRound(v);
	auto vdist = Vec2<float>(Constants::FloatMax, Constants::FloatMax);
	int ClosestHash = 0;

	float CellularJitter = 0.5f * State.CellularJitterModifier;

	int xPrimed = (vr.X - 1) * Constants::PrimeX;
	int yPrimedBase = (vr.Y - 1) * Constants::PrimeY;

	switch (Config.CellularDistanceFunc)
	{
	default:
	case ECellularDistanceFunction::Euclidean:
	case ECellularDistanceFunction::EuclideanSquared:
		for (int xi = vr.X - 1; xi <= vr.X + 1; xi++)
		{
			int yPrimed = yPrimedBase;
			for (int yi = vr.Y - 1; yi < vr.Y + 1; yi++)
			{
				int Hash = Hash2D({ xPrimed, yPrimed });
				int idx = Hash & (255 << 1);
				auto vec = Vec2<float>(
					(float)(xi - v.X) + Constants::RandVecs2D[idx] * CellularJitter,
					(float)(yi - v.Y) + Constants::RandVecs2D[idx | 1] * CellularJitter);
				float NewDistance = vec.X * vec.X + vec.Y * vec.Y;

				vdist.Y = FastMax({FastMin({ vdist.Y, NewDistance }), vdist.X
			});
				if (NewDistance < vdist.X)
				{
					vdist.X = NewDistance;
					ClosestHash = Hash;
				}
				yPrimed += Constants::PrimeY;
			}
			xPrimed += Constants::PrimeY;
		}
		break;

	case ECellularDistanceFunction::ManHatten:
		for (int xi = vr.X - 1; xi <= vr.X + 1; xi++)
		{
			int yPrimed = yPrimedBase;

			for (int yi = vr.Y - 1; yi < vr.Y + 1; yi++)
			{
				int Hash = Hash2D({ xPrimed, yPrimed });
				int idx = Hash & (255 << 1);

				auto vec = Vec2<float>(
					(float)(xi - v.X) + Constants::RandVecs2D[idx] * CellularJitter,
					(float)(yi - v.Y) + Constants::RandVecs2D[idx | 1] * CellularJitter);

				float NewDistance = FastAbs(vec.X) + FastAbs(vec.Y);

				vdist.Y = FastMax({FastMin({ vdist.Y, NewDistance }), vdist.X
			});
				if (NewDistance < vdist.X)
				{
					vdist.X = NewDistance;
					ClosestHash = Hash;
				}
				yPrimed += Constants::PrimeY;
			}
			xPrimed += Constants::PrimeY;
		}
		break;
	case ECellularDistanceFunction::Hybrid:
		for (int xi = vr.X - 1; xi <= vr.X + 1; xi++)
		{
			int yPrimed = yPrimedBase;

			for (int yi = vr.Y - 1; yi < vr.Y + 1; yi++)
			{
				int Hash = Hash2D({ xPrimed, yPrimed });
				int idx = Hash & (255 << 1);

				auto vec = Vec2<float>(
					(float)(xi - v.X) + Constants::RandVecs2D[idx] * CellularJitter,
					(float)(yi - v.Y) + Constants::RandVecs2D[idx | 1] * CellularJitter);
				float NewDistance = (FastAbs(vec.X) + FastAbs(vec.Y)) + (vec.X * vec.X + vec.Y * vec.Y);


				vdist.Y = FastMax({FastMin({ vdist.Y, NewDistance }), vdist.X});
				if (NewDistance < vdist.X)
				{
					vdist.X = NewDistance;
					ClosestHash = Hash;
				}
				yPrimed += Constants::PrimeY;
			}
			xPrimed += Constants::PrimeY;
		}
		break;
	}

	if (Config.CellularDistanceFunc == ECellularDistanceFunction::Euclidean && (
		Config.CellularReturnType == ECellularReturnType::Distance
		|| Config.CellularReturnType == ECellularReturnType::Distance2))
	{
		vdist.X = FastSquareRoot(vdist.X);
		if (Config.CellularReturnType == ECellularReturnType::Distance2)
		{
			vdist.Y = FastSquareRoot(vdist.Y);
		}
	}

	switch (Config.CellularReturnType)
	{
	case ECellularReturnType::CellValue:
		return ClosestHash * (1 / Constants::HashFloatConst);
	case ECellularReturnType::Distance:
		return vdist.X - 1;
	case ECellularReturnType::Distance2:
		return vdist.Y - 1;
	case ECellularReturnType::Distance2Add:
		return (vdist.Y + vdist.X) * 0.5f - 1;
	case ECellularReturnType::Distance2Sub:
		return vdist.Y - vdist.X - 1;
	case ECellularReturnType::Distance2Mul:
		return vdist.Y * vdist.X * 0.5f - 1;
	case ECellularReturnType::Distance2Div:
		return vdist.X / vdist.Y - 1;
	default:
		return 0;
	}
}

float Noise::Cellular3D(Vec3<float> v)
{
	return 0;
}

float Noise::Perlin2D(Vec2<float> v)
{
	return 0;
}

float Noise::Perlin3D(Vec3<float> v)
{
	return 0;
}

float Noise::ValueCubic2D(Vec2<float> v)
{
	return 0;
}

float Noise::ValueCubic3D(Vec3<float> v)
{
	return 0;
}

float Noise::Value2D(Vec2<float> v)
{
	return 0;
}

float Noise::Value3D(Vec3<float> v)
{
	return 0;
}


void Noise::DomainWarpSingle3D(Vec3<float> v)
{

}
void Noise::DomainWarpFractalProgressive3D(Vec3<float> v)
{

}
void Noise::DomainWarpFractalIndependent3D(Vec3<float> v)
{

}