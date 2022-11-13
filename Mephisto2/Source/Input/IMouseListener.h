#pragma once
#include <Types.h>
#include <Math/Math.h>

namespace ME::Input {
	class IMouseListener
	{
	public:
		IMouseListener();
		virtual ~IMouseListener();
		virtual void OnMouseMove(const Vec2<float>& position) {};
		virtual void OnMouseButtonDown(const Vec2<float>& position, int button) {};
		virtual void OnMouseButtonUp(const Vec2<float>& position, int button) {};
		virtual void OnMouseWheel(const Vec2<float>& position, const Vec2<float>& ScrollAmount) {};
	};
}