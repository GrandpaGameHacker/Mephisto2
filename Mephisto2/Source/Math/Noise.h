#pragma once
/// <summary>
/// Inspired and Adapted from https://github.com/Auburn/FastNoiseLite/blob/master/C/FastNoiseLite.h
/// Thank you Jordan Peck.
/// </summary>
/// 
#include <Math/3D/Vector.inl>

namespace ME::Math
{
	enum class ENoiseType : unsigned char
	{
		Perlin,
		OpenSimplex2,
		OpenSimplex2S,
		Value,
		ValueCubic,
		Cellular,
	};

	enum class ERotation3DType : unsigned char
	{
		None,
		ImproveXYPlanes,
		ImproveYZPlanes,
	};

	enum class EFractalType : unsigned char
	{
		None,
		FBM,
		Ridged,
		PingPong,
		DomainWarpProgressive,
		DomainWarpIndependent,
	};

	enum class ECellularDistanceFunction : unsigned char
	{
		Euclidean,
		EuclideanSquared,
		ManHatten,
		Hybrid,
	};

	enum class  ECellularReturnType : unsigned char
	{
		CellValue,
		Distance,
		Distance2,
		Distance2Add,
		Distance2Sub,
		Distance2Mul,
		Distance2Div,
	};

	enum class EDomainWarpType : unsigned char
	{
		OpenSimplex2,
		OpenSimplex2Reduced,
		BasicGrid,
	};

	struct NoiseSettings
	{
		ENoiseType						NoiseType = ENoiseType::OpenSimplex2;
		ERotation3DType					Rotation3DType = ERotation3DType::None;
		EFractalType					FractalType = EFractalType::DomainWarpIndependent;
		ECellularDistanceFunction		CellularDistanceFunc = ECellularDistanceFunction::EuclideanSquared;
		ECellularReturnType				CellularReturnType = ECellularReturnType::Distance;
		EDomainWarpType					DomainWarpType = EDomainWarpType::OpenSimplex2;
	};

	struct NoiseState
	{
		/// <summary>
		/// Seed used for noise generation.
		/// <remarks>Default: 0xDEADBEEF</remarks>
		/// </summary>
		int Seed = 0xDEADBEEF;

		/// <summary>
		/// Frequency used for noise generation.
		/// <remarks>Default: 0.01f</remarks>
		/// </summary>
		float Frequency = 0.01f;

		/// <summary>
		/// Octave for fractal noise types.
		/// <remarks>Default: 3</remarks>
		/// </summary>
		int Octaves = 3;

		/// <summary>
		/// Octave Lacunarity for fractal noise types.
		/// <remarks>Default: 2.0f</remarks>
		/// </summary>
		float Lacunarity = 2.0f;

		/// <summary>
		/// Octave gain for fractal noise types.
		/// <remarks>Default: 0.5f</remarks>
		/// </summary>
		float Gain = 0.5;

		/// <summary>
		/// Octave weighting for non Domain Warp fractal types.
		/// <remarks>Default: 0.0f</remarks>
		/// </summary>
		float WeightedStrength = 0.f;

		/// <summary>
		/// Strength of the fractal PingPong effect.
		/// <remarks>Default: 2.0f</remarks>	
		/// </summary>
		float PingPongStrength = 2.0f;

		/// <summary>
		/// Maximum distance a cellular point can move from it's grid position.
		/// <remarks>Default: 1.0f</remarks>
		/// <remarks>Setting above 1.0f causes artifacts</remarks>
		/// </summary>
		float CellularJitterModifier = 1.0f;

		/// <summary>
		/// Maximum warp distance from original position for Domain Warp
		/// <remarks>Default: 1.0</remarks>
		/// </summary>
		float DomainWarpAmplitude = 1.0f;
	};

	class Noise
	{
	public:
		Noise();
		~Noise() {};

		//////////////////////////////////////////////////////////////////////////
		// Config Getters
		//////////////////////////////////////////////////////////////////////////

		NoiseState& GetState();
		NoiseSettings& GetSettings();

		//////////////////////////////////////////////////////////////////////////
		// Config Setters
		//////////////////////////////////////////////////////////////////////////

		void SetBasicType(ENoiseType Type);
		void SetRotation3DType(ERotation3DType Type);
		void SetFractalType(EFractalType Type);
		void SetDomainWarpType(EDomainWarpType Type);
		void SetCellularDistanceFunction(ECellularDistanceFunction Function);
		void SetCellularReturnType(ECellularReturnType ReturnType);

		void SetSeed(int seed);
		void SetFrequency(float frequency);
		void FractalSetOctave(int octave);
		void FractalSetLacunarity(float lacunarity);
		void FractalSetGain(float gain);
		void FractalSetWeightedStrength(float strength);
		void FractalSetPingPongStrength(float strength);
		void CellularSetJitter(float jitterAmount);
		void DomainWarpSetAmplitude(float amplitude);


		//////////////////////////////////////////////////////////////////////////
		// Noise Generation functions
		//////////////////////////////////////////////////////////////////////////
		
		/// <summary>
		/// Generates 2D Noise from the current Noise Settings
		/// </summary>
		float GetNoise2D(Vec2<float>& v);

		/// <summary>
		/// Generates 3D Noise from the current Noise Settings
		/// </summary>
		float GetNoise3D(Vec3<float>& v);

		void DomainWarp2D(Vec2<float>& v);
		void DomainWarp3D(Vec3<float>& v);

	protected:
		NoiseState State;
		NoiseSettings Config;
	private:

		//////////////////////////////////////////////////////////////////////////
		// Internal Utility Functions
		//////////////////////////////////////////////////////////////////////////

		float FastMin(const Vec2<float>& vIn);
		float FastMax(const Vec2<float>& vIn);
		float FastAbs(float fIn);
		float CastInt2Float(int in);
		int   CastFloat2Int(float in);
		float InverseSquareRoot(float in);
		float FastSquareRoot(float in);

		float FastFloor(float in);
		Vec2<float> FastFloor(Vec2<float> In);
		Vec3<float> FastFloor(Vec3<float> in);

		float FastRound(float in);
		Vec2<float> FastRound(Vec2<float> in);
		Vec3<float> FastRound(Vec3<float> in);
		float Lerp(float a, float b, float t);
		float CubicLerp(float a, float b, float c,float d, float t);
		float InterpolateHermite(float t);
		float InterpolateQuintic(float t);
		float PingPong(float t);
		float CalculateFractalBounding();


		int Hash2D(Vec2<int> vPrimed);
		int Hash3D(Vec3<int> vPrimed);

		float ValueCoordinate2D(Vec2<int> vPrimed);
		float ValueCoordinate2D(Vec3<int> vPrimed);
		
		float GradientCoordinate2D(Vec2<int> vPrimed, Vec2<float> vIn);
		float GradientCoordinate3D(Vec3<int> vPrimed, Vec3<float> vIn);

		void GradientCoordinateOutput2D(Vec2<int> vPrimed, Vec2<float>& vOut);
		void GradientCoordinateOutput3D(Vec3<int> vPrimed, Vec3<float>& vOut);

		void GradientCoordinateDual2D(Vec2<int> vPrimed, Vec2<float> vIn, Vec2<float>& vOut);
		void GradientCoordinateDual3D(Vec3<int> vPrimed, Vec3<float> vIn, Vec3<float>& vOut);


		//////////////////////////////////////////////////////////////////////////
		// Internal Gen Functions
		//////////////////////////////////////////////////////////////////////////

		float Simplex2D(Vec2<float> v);
		float OpenSimplex2_3D(Vec3<float> v);
		float OpenSimplex2S_2D(Vec2<float> v);
		float OpenSimplex2S_3D(Vec3<float> v);

		float Cellular2D(Vec2<float> v);
		float Cellular3D(Vec3<float> v);

		float Perlin2D(Vec2<float> v);
		float Perlin3D(Vec3<float> v);

		float ValueCubic2D(Vec2<float> v);
		float ValueCubic3D(Vec3<float> v);	
		float Value2D(Vec2<float> v);
		float Value3D(Vec3<float> v);

		void DomainWarpSingle2D(Vec2<float> v);
		void DomainWarpFractalProgressive2D(Vec2<float> v);
		void DomainWarpFractalIndependent2D(Vec2<float> v);

		void DomainWarpSingle3D(Vec3<float> v);
		void DomainWarpFractalProgressive3D(Vec3<float> v);
		void DomainWarpFractalIndependent3D(Vec3<float> v);
	};
}
