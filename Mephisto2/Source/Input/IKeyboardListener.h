#pragma once
#include <Types.h>
namespace ME::Input {
	class IKeyboardListener
	{
	public:
		IKeyboardListener() {};
		virtual ~IKeyboardListener() {};
		virtual OnKeyDown(int key, uint16 unicode) {};
		virtual OnKeyUp(int key, uint16 unicode) {};
	};
}
