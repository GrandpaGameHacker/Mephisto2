#include "Platform.h"
const char* ME::Platform::GetPlatformName()
{
#ifdef WINDOWS
	return "Microsoft_Windows";
#endif
}

void ME::Platform::DPIScaling()
{
#ifdef WINDOWS
	ME::Platform::Windows::DPIScaling();
#endif
}
