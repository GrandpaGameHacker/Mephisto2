#include "Noise.h"
#include "NoiseConstants.h"
#include "Types.h"
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

void Noise::SetCullularDistanceFunction(ECellularDistanceFunction Function)
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

}

void Noise::DomainWarp3D(Vec3<float>& v)
{

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

float Noise::FastRound(float in)
{
	return in >= 0 ? (int)(in + 0.5f) : (int)(in - 0.5f);
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

}

float Noise::OpenSimplex2_3D(Vec3<float> v)
{

}

float Noise::OpenSimplex2S_2D(Vec2<float> v)
{

}

float Noise::OpenSimplex2S_3D(Vec3<float> v)
{

}

float Noise::Cellular2D(Vec2<float> v)
{

}

float Noise::Cellular3D(Vec3<float> v)
{

}

float Noise::Perlin2D(Vec2<float> v)
{

}

float Noise::Perlin3D(Vec3<float> v)
{

}

float Noise::ValueCubic2D(Vec2<float> v)
{

}

float Noise::ValueCubic3D(Vec3<float> v)
{

}

float Noise::Value2D(Vec2<float> v)
{

}

float Noise::Value3D(Vec3<float> v)
{

}
