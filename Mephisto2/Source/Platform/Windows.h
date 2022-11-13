#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS true
#include <Windows.h>
#endif
namespace ME::Platform::Windows {
	void DPIScaling();
}
