#include "StringUtils.h"
#include <spdlog/spdlog.h>
#include <Core/MephistoAssert.h>
#include <stdexcept>

void ME::StringUtils::Split(const string& source, int index, string& left, string& right)
{
	MEPH_ASSERT(index > 0);
	MEPH_ASSERT(index < source.length());
	left = string(source.substr(0, index));
	right = string(source.substr(index + 1, source.length()));
}

bool ME::StringUtils::Split(const string& source, char delimiter, string& left, string& right)
{
	size_t index = source.find_first_of(delimiter, 0);
	if (index < 0) return false;
	left = string(source.substr(0, index));
	right = string(source.substr(index + 1, source.length()));
	return true;
}

bool ME::StringUtils::Replace(string& str, const string& from, const string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

bool ME::StringUtils::IsIntegerNumber(const string& source)
{
	uint64 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = stoull(source, &LDX, 10);
	}
	catch (invalid_argument e)
	{
		return false;
	}
	catch (out_of_range e)
	{
		return false;
	}
	return true;
}

bool ME::StringUtils::IsHexNumber(const string& source)
{
	uint64 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = stoull(source, &LDX, 16);
	}
	catch (invalid_argument e)
	{
		return false;
	}
	catch (out_of_range e)
	{
		return false;
	}
	return true;
}

bool ME::StringUtils::IsValidNumber(const string& source, ENumberBase base)
{
	switch (base)
	{
	case ENumberBase::Decimal:
		if (!IsIntegerNumber(source))
		{
			return false;
		}
		break;
	case ENumberBase::Hexadecmal:
		if (!IsHexNumber(source))
		{
			return false;
		}
		break;
	case ENumberBase::Binary:
	case ENumberBase::Octal:
	default:
		spdlog::error("No validity check for number base");
		return false;
	}
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, uint64& value, ENumberBase base)
{
	if (!IsValidNumber(source, base))
	{
		spdlog::error("StringUtils::TryCastTo() -> {} is not a valid number to convert to (yet?)");
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	uint64 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = stoull(source, &LDX, number_base);
	}
	catch (invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (out_of_range e)
	{
		spdlog::error("StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(uint64).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, uint32& value, ENumberBase base)
{
	if (!IsValidNumber(source, base))
	{
		spdlog::error("StringUtils::TryCastTo() -> {} is not a valid number to convert to (yet?)");
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	uint32 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stoul(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(uint32).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, uint16& value, ENumberBase base)
{
	if (!IsIntegerNumber(source))
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is not a valid number", source);
		return false;
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	int16 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stos(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(int16).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, int64& value, ENumberBase base)
{
	if (!IsIntegerNumber(source))
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is not a valid number", source);
		return false;
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	int64 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stoll(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(int64).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, int32& value, ENumberBase base)
{
	if (!IsIntegerNumber(source))
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is not a valid number", source);
		return false;
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	int32 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stoi(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(int32).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, uint8& value, ENumberBase base)
{
	if (!IsIntegerNumber(source))
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is not a valid number", source);
		return false;
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	uint8 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stouc(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(uint8).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, int16& value, ENumberBase base)
{
	if (!IsIntegerNumber(source))
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is not a valid number", source);
		return false;
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	int16 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stos(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(int16).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, int8& value, ENumberBase base)
{
	if (!IsIntegerNumber(source))
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is not a valid number", source);
		return false;
	}
	int number_base = static_cast<std::underlying_type<ENumberBase>::type>(base);
	uint8 TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stouc(source, &LDX, number_base);
	}
	catch (std::invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (std::out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(uint8).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, float& value)
{
	float TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = stof(source, &LDX);
	}
	catch (invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(float).name());
		return false;
	}
	value = TestValue;
	return true;
}

bool ME::StringUtils::TryCastTo(const string& source, double& value)
{
	double TestValue = 0;
	size_t LDX = 0;
	try
	{
		TestValue = std::stod(source, &LDX);
	}
	catch (invalid_argument e)
	{
		spdlog::error(e.what());
		return false;
	}
	catch (out_of_range e)
	{
		spdlog::error("ME::StringUtils::TryCastTo() -> {} is out of range of type {}", e.what(), typeid(double).name());
		return false;
	}
	value = TestValue;
	return true;
}


void ME::StringUtils::internal::TestAll()
{
	spdlog::debug("Testing all StringUtil functions...");
	auto TestNumberString = []<typename T>(const string & Test, T & TestType)
	{

		IsIntegerNumber(Test);
		bool bTryCastTo = TryCastTo(Test, TestType);
		if (!bTryCastTo)
		{
			spdlog::error("TryCastTo({},..) failed to cast to type {}", Test, typeid(TestType).name());
		}
		else
		{
			spdlog::debug("TryCastTo(...) converted \"{}\" to {}\n\n", Test, TestType);
		}
	};

	auto TestNumberHexString = []<typename T>(const string & Test, T & TestType)
	{

		bool bTryCastTo = TryCastTo(Test, TestType, ENumberBase::Hexadecmal);
		if (!bTryCastTo)
		{
			spdlog::error("TryCastTo(\"{}\",..) failed to cast to type {}", Test, typeid(TestType).name());
		}
		else
		{
			spdlog::debug("TryCastTo(...) converted \"{}\" to {}\n\n", Test, TestType);
		}
	};
	uint8 UTest1 = 0;
	uint16 UTest2 = 0;
	uint32 UTest3 = 0;
	uint64 UTest4 = 0;

	int8 Test1 = 0;
	int16 Test2 = 0;
	int32 Test3 = 0;
	int64 Test4 = 0;

	float FTest = 0;
	double DTest = 0;

	TestNumberString("256", UTest1);
	TestNumberString("-255", UTest1);
	TestNumberString("+255", UTest1);
	TestNumberString("255", UTest1);

	TestNumberString("127", Test1);
	TestNumberString("127", Test2);

	TestNumberString("65536", UTest2);
	TestNumberString("65535", UTest2);

	TestNumberString("4294967295", UTest3);
	TestNumberString("4294967296", UTest3);

	TestNumberString("18446744073709551615", UTest4);
	TestNumberString("18446744073709551616", UTest4);

	TestNumberString("14.5", FTest);
	TestNumberString("69.69", DTest);

	uint64 TestHex = 0;
	TestNumberHexString("0x11f234", TestHex);
	TestNumberHexString("ffff", TestHex);
	TestNumberHexString("ggg", TestHex);
	TestNumberString("prenis", UTest4);
}