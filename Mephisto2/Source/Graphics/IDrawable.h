#pragma once
class IDrawable
{
	IDrawable() = default;
	virtual ~IDrawable() {};
	virtual void Draw() = 0;
	virtual bool IsVisible() = 0;
};

