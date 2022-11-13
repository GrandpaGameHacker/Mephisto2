#include "IMouseListener.h"
#include <Input/Mouse.h>
ME::Input::IMouseListener::IMouseListener()
{
	Mouse::Get()->AddListener(this);
}

ME::Input::IMouseListener::~IMouseListener()
{
	Mouse::Get()->RemoveListener(this);
}
