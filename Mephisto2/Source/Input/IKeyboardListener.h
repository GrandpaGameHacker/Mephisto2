#pragma once
#include <Types.h>

namespace ME::Input
{
	class IKeyboardListener
	{
	public:
		IKeyboardListener();
		virtual ~IKeyboardListener();
		virtual void OnKeyDown(int key, uint16 unicode) {};
		virtual void OnKeyUp(int key, uint16 unicode) {};
	};
}
