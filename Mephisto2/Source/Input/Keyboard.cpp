#include <Input/Keyboard.h>
#include <Input/IKeyboardListener.h>
#include <SDL2/SDL.h>
#include <Core/MephistoAssert.h>
#include <algorithm>
std::shared_ptr<ME::Input::Keyboard> ME::Input::Keyboard::GKeyboard;

ME::Input::Keyboard::Keyboard()
{

}

ME::Input::Keyboard::~Keyboard()
{

}

void ME::Input::Keyboard::OnStartFrame()
{
	for (size_t i = 0; i < KeysJustDown.size(); i++)
	{
		KeysJustDown[i] = false;
		KeysJustUp[i] = false;
	}
}

std::shared_ptr< ME::Input::Keyboard>  ME::Input::Keyboard::Get()
{
	if (!GKeyboard)
	{
		GKeyboard = std::make_shared<Keyboard>();
	}
	return GKeyboard;
}

void ME::Input::Keyboard::AddListener(IKeyboardListener* listener)
{
	if (listener)
	{
		Listeners.push_back(listener);
	}
}

void ME::Input::Keyboard::RemoveListener(IKeyboardListener* listener)
{
	std::vector<IKeyboardListener*>::iterator iter = std::find(Listeners.begin(), Listeners.end(), listener);
	if (iter != Listeners.end())
	{
		Listeners.erase(iter);
	}
}

void ME::Input::Keyboard::SetKeyDown(int key, bool bDown)
{
	if (key < 0 || key > 400) return;

	if (key >= (int)KeysDown.size())
	{
		KeysDown.resize(key + 1);
		KeysJustDown.resize(key + 1);
		KeysJustUp.resize(key + 1);
	}

	KeysDown[key] = bDown;

	if (bDown)
	{
		KeysJustDown[key] = true;
	}
	else
	{
		KeysJustUp[key] = true;
	}
}

bool ME::Input::Keyboard::IsKeyDown(int button) const
{
	if (button >= 0 && button < (int)KeysDown.size())
	{
		return KeysDown[button];
	}
	return false;
}

bool ME::Input::Keyboard::IsKeyJustDown(int button) const
{
	if (button >= 0 && button < (int)KeysJustDown.size())
	{
		return KeysJustDown[button];
	}
	return false;
}

bool ME::Input::Keyboard::IsKeyJustUp(int button) const
{
	if (button >= 0 && button < (int)KeysJustUp.size())
	{
		return KeysJustUp[button];
	}
	return false;
}

bool ME::Input::Keyboard::IsShiftDown()
{
	return IsKeyDown(LSHIFT) || IsKeyDown(RSHIFT);
}

bool ME::Input::Keyboard::IsAltDown()
{
	return IsKeyDown(LALT) || IsKeyDown(RALT);
}

bool ME::Input::Keyboard::IsCtrlDown()
{
	return IsKeyDown(LCTRL) || IsKeyDown(RCTRL);
}

bool ME::Input::Keyboard::IsLeftShiftDown()
{
	return IsKeyDown(LSHIFT);
}

bool ME::Input::Keyboard::IsRightShiftDown()
{
	return IsKeyDown(RSHIFT);
}

bool ME::Input::Keyboard::IsLeftAltDown()
{
	return IsKeyDown(LALT);
}

bool ME::Input::Keyboard::IsRightAltDown()
{
	return IsKeyDown(RALT);
}

bool ME::Input::Keyboard::IsLeftCtrlDown()
{
	return IsKeyDown(LCTRL);
}

bool ME::Input::Keyboard::IsRightCtrlDown()
{
	return IsKeyDown(RCTRL);
}

bool ME::Input::Keyboard::IsCapslockEnabled()
{
	int mod = SDL_GetModState();
	mod &= KMOD_CAPS;
	return (bool)(mod == KMOD_CAPS);
}

bool ME::Input::Keyboard::IsNumlockEnabled()
{
	int mod = SDL_GetModState();
	mod &= KMOD_NUM;
	return (bool)(mod == KMOD_NUM);
}

bool ME::Input::Keyboard::IsScrollLockEnabled()
{
	int mod = SDL_GetModState();
	mod &= KMOD_SCROLL;
	return (bool)(mod == KMOD_SCROLL);
}

void ME::Input::Keyboard::TriggerKeyDownEvent(int button)
{
	size_t listener_count = Listeners.size();
	for (size_t i = 0; i < listener_count; i++)
	{
		MEPH_ASSERT(Listeners[i]);
		Listeners[i]->OnKeyDown(button);
	}
	SetKeyDown(button, true);
}

void ME::Input::Keyboard::TriggerKeyUpEvent(int button)
{
	size_t listener_count = Listeners.size();
	for (size_t i = 0; i < listener_count; i++)
	{
		MEPH_ASSERT(Listeners[i]);
		Listeners[i]->OnKeyUp(button);
	}
	SetKeyDown(button, true);
}
