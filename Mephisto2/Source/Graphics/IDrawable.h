#pragma once
 class IDrawable
{
	 IDrawable();
	 virtual ~IDrawable() {};
	 virtual void Draw() = 0;
	 virtual bool IsVisible() { return false;  };
};

