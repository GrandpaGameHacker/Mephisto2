#include "Windows.h"
#include <SDL2/SDL.h>
void ME::Platform::Windows::DPIScaling()
{
#ifdef WINDOWS
	typedef enum PROCESS_DPI_AWARENESS
	{
		PROCESS_DPI_UNAWARE = 0,
		PROCESS_SYSTEM_DPI_AWARE = 1,
		PROCESS_PER_MONITOR_DPI_AWARE = 2
	} PROCESS_DPI_AWARENESS;

	void* userDLL;
	BOOL(WINAPI * SetProcessDPIAware)(void) = nullptr; // Vista and later
	void* shcoreDLL;
	HRESULT(WINAPI * SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS dpiAwareness) = nullptr; // Windows 8.1 and later

	userDLL = SDL_LoadObject("USER32.DLL");
	if (userDLL)
	{
		SetProcessDPIAware = (BOOL(WINAPI*)(void)) SDL_LoadFunction(userDLL, "SetProcessDPIAware");
	}

	shcoreDLL = SDL_LoadObject("SHCORE.DLL");
	if (shcoreDLL)
	{
		SetProcessDpiAwareness = (HRESULT(WINAPI*)(PROCESS_DPI_AWARENESS)) SDL_LoadFunction(shcoreDLL, "SetProcessDpiAwareness");
	}

	if (SetProcessDpiAwareness)
	{
		/* Try Windows 8.1+ version */
		const HRESULT result = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		SDL_Log("called SetProcessDpiAwareness: %d\n", (result == S_OK) ? 1 : 0);
	}
	else if (SetProcessDPIAware)
	{
		/* Try Vista - Windows 8 version.
		This has a constant scale factor for all monitors.
		*/
		const BOOL success = SetProcessDPIAware();
		SDL_Log("called SetProcessDPIAware: %d\n", static_cast<int>(success));
	}
#endif
}
