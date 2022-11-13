#include "Keyboard.h"

std::shared_ptr<ME::Input::Keyboard> ME::Input::Keyboard::GKeyboard;

ME::Input::Keyboard::Keyboard()
{

}

ME::Input::Keyboard::~Keyboard()
{

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
