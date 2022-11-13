#pragma once
#include <Types.h>

namespace ME::Input
{
	class IKeyboardListener
	{
	public:
		IKeyboardListener();
		virtual ~IKeyboardListener();
		virtual void OnKeyDown(int key) {};
		virtual void OnKeyUp(int key) {};
	};
}
