#pragma once
#include <Types.h>
#include <Math/Math.h>
namespace ME::Input {
	class IMouseListener
	{
	public:
		IMouseListener() {};
		virtual ~IMouseListener() {};
		virtual void OnMove(const Vec2<float>& position) {};
		virtual void OnButtonDown(const Vec2<float>& position, int button) {};
		virtual void OnButtonUp(const Vec2<float>& position, int button) {};
	};
}