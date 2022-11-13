#include <Input/Mouse.h>
#include <Core/MephistoAssert.h>
std::shared_ptr<ME::Input::Mouse> ME::Input::Mouse::GMouse;
ME::Input::Mouse::Mouse() :
    bIsVisible(true),
    Position(0.f, 0.f),
    ButtonsDown(NumberOfButtons),
    ButtonsJustDown(NumberOfButtons),
    ButtonsJustUp(NumberOfButtons)
{
    for (size_t i = 0; i < ButtonsJustDown.size(); i++)
	{
        ButtonsJustDown[i] = false;
        ButtonsJustUp[i] = false;
	}
}

std::shared_ptr<ME::Input::Mouse> ME::Input::Mouse::Get()
{
    if (!GMouse)
    {
        GMouse = std::make_shared<Mouse>();
    }
    return GMouse;
}

void ME::Input::Mouse::Show()
{
    SetVisibility(true);
}

void ME::Input::Mouse::Hide()
{
    SetVisibility(false);
}

bool ME::Input::Mouse::SetVisibility(bool bShowCursor)
{
    bIsVisible = bShowCursor;
    return bIsVisible;
}

Vec2<float> ME::Input::Mouse::GetPos() const
{
    return Position;
}

bool ME::Input::Mouse::IsDown(int button) const
{
    if (button >= 0 && button < ButtonsJustDown.size())
    {
        return ButtonsJustDown[button];
    }
    return false;
}

bool ME::Input::Mouse::IsUp(int button) const
{
	if (button >= 0 && button < ButtonsJustUp.size())
	{
		return ButtonsJustUp[button];
	}
    return false;
}

void ME::Input::Mouse::OnStartFrame()
{
    for (size_t i = 0; i < ButtonsJustDown.size(); i++)
    {
        ButtonsJustDown[i] = false;
        ButtonsJustUp[i] = false;
    }
}
void ME::Input::Mouse::AddListener(IMouseListener* listener)
{
    if (listener)
    {
        Listeners.push_back(listener);
    }
}		

void ME::Input::Mouse::RemoveListener(IMouseListener* listener)
{
    std::vector<IMouseListener*>::iterator iter = std::find(Listeners.begin(), Listeners.end(), listener);
    if (iter != Listeners.end())
    {
        Listeners.erase(iter);
    }
}

void ME::Input::Mouse::TriggerMoveEvent(const Vec2<float>& position)
{
    Position = position;
    for (auto& listener : Listeners)
    {
        MEPH_ASSERT(listener);
        listener->OnMouseMove(position);
    }
}

void ME::Input::Mouse::TriggerButtonDownEvent(const Vec2<float>& position, int button)
{
	Position = position;
	for (auto& listener : Listeners)
	{
        MEPH_ASSERT(listener);
		listener->OnMouseButtonDown(position, button);
	}

    if (button >= 0 && button < (int)ButtonsDown.size())
    {
        ButtonsDown[button] = true;
        ButtonsJustDown[button] = true;
    }
}

void ME::Input::Mouse::TriggerButtonUpEvent(const Vec2<float>& position, int button)
{
	Position = position;
    ButtonsJustUp[button] = true;
	for (auto& listener : Listeners)
	{
        MEPH_ASSERT(listener);
		listener->OnMouseButtonUp(position, button);
	}
	if (button >= 0 && button < (int)ButtonsJustUp.size())
	{
		ButtonsDown[button] = false;
		ButtonsJustUp[button] = true;
	}
}

void ME::Input::Mouse::TriggerScrollwheelEvent(const Vec2<float>& position, const Vec2<float>& ScrollAmount)
{
    Position = position;
	for (auto& listener : Listeners)
	{
		MEPH_ASSERT(listener);
		listener->OnMouseWheel(position, ScrollAmount);
	}
}
