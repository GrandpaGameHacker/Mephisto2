#include "Mouse.h"

ME::Input::Mouse::Mouse() :
    bIsVisible(true),
    Position(0.f, 0.f),
    ButtonsDown(NumberOfButtons),
    ButtonsUp(NumberOfButtons)
{
    for (size_t i = 0; i < ButtonsDown.size(); i++)
	{
        ButtonsDown[i] = false;
        ButtonsUp[i] = false;
	}
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
    if (button >= 0 && button < ButtonsDown.size())
    {
        return ButtonsDown[button];
    }
    return false;
}

bool ME::Input::Mouse::IsUp(int button) const
{
	if (button >= 0 && button < ButtonsUp.size())
	{
		return ButtonsUp[button];
	}
    return false;
}

void ME::Input::Mouse::OnStartFrame()
{
    for (size_t i = 0; i < ButtonsDown.size(); i++)
    {
        ButtonsDown[i] = false;
        ButtonsUp[i] = false;
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
    std::vector<IMouseListener*> ::iterator iter = std::find(Listeners.begin(), Listeners.end(), listener);
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
        listener->OnMove(position);
    }
}

void ME::Input::Mouse::TriggerButtonDownEvent(const Vec2<float>& position, int button)
{
	Position = position;
	for (auto& listener : Listeners)
	{
		listener->OnButtonDown(position, button);
	}
}

void ME::Input::Mouse::TriggerButtonUpEvent(const Vec2<float>& position, int button)
{
	Position = position;
	for (auto& listener : Listeners)
	{
		listener->OnButtonUp(position, button);
	}
}
