#include "IKeyboardListener.h"
#include "Keyboard.h"

ME::Input::IKeyboardListener::IKeyboardListener()
{
	Keyboard::Get()->AddListener(this);
}

ME::Input::IKeyboardListener::~IKeyboardListener()
{
	Keyboard::Get()->RemoveListener(this);
}
