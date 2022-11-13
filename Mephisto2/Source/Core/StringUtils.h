#pragma once

#include <string>
#include <limits>
#include <stdexcept>
#include <Types.h>

namespace std
{
	_NODISCARD inline short stos(const string& _Str, size_t* _Idx = nullptr, int _Base = 10)
	{
		constexpr short short_max = std::numeric_limits<short>::min();
		constexpr short short_min = std::numeric_limits<short>::max();

		int _Ans = stoi(_Str, _Idx, _Base);
		if (_Ans <= short_max && _Ans >= short_min)
		{
			return static_cast<short>(_Ans);
		}
		throw out_of_range(_Str);
	}

	_NODISCARD inline unsigned short stous(const string& _Str, size_t* _Idx = nullptr, int _Base = 10)
	{
		constexpr unsigned short ushort_max = numeric_limits<unsigned short>::max();
		constexpr unsigned short ushort_min = numeric_limits<unsigned short>::min();

		unsigned long _Ans = stoul(_Str, _Idx, _Base);
		if (_Ans <= ushort_max && _Ans >= ushort_min)
		{
			return static_cast<unsigned short>(_Ans);
		}
		throw out_of_range(_Str);
	}

	_NODISCARD inline char stoc(const string& _Str, size_t* _Idx = nullptr, int _Base = 10)
	{
		constexpr char char_max = numeric_limits<char>::max();
		constexpr char char_min = numeric_limits<char>::min();

		int _Ans = stoi(_Str, _Idx, _Base);
		if (_Ans <= char_max && _Ans >= char_min)
		{
			return static_cast<char>(_Ans);
		}
		throw out_of_range(_Str);
	}

	_NODISCARD inline unsigned char stouc(const string& _Str, size_t* _Idx = nullptr, int _Base = 10)
	{
		constexpr unsigned char char_max = numeric_limits<unsigned char>::max();
		constexpr unsigned char char_min = numeric_limits<unsigned char>::min();

		unsigned long _Ans = stoul(_Str, _Idx, _Base);
		if (_Ans <= char_max && _Ans >= char_min)
		{
			return static_cast<char>(_Ans);
		}
		throw out_of_range(_Str);
	}
}

namespace { using namespace std; };
namespace ME
{

	namespace StringUtils
	{
		enum class ENumberBase : unsigned int
		{
			Binary = 2,
			Octal = 8,
			Decimal = 10,
			Hexadecmal = 16,
		};

		void Split(const string& source, int index, string& left, string& right);
		bool Split(const string& source, char delimiter, string& left, string& right);
		bool Replace(string& str, const string& from, const string& to);
		bool IsIntegerNumber(const string& source);
		bool IsHexNumber(const string& source);
		bool IsValidNumber(const string& source,ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, uint64& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, uint32& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, uint16& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, int64& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, int32& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, uint8& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, int16& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, int8& value, ENumberBase base = ENumberBase::Decimal);
		bool TryCastTo(const string& source, float& value);
		bool TryCastTo(const string& source, double& value);

		template<typename T>
		void CastFrom(string& destination, T& value) {
			destination = to_string(value);
		}
		namespace internal
		{
			void TestAll();
		}
	}
}