#pragma once
namespace ME::Input {
	class Gamepad;
	class IGamepadListener
	{
	public:
		IGamepadListener() {};
		virtual ~IGamepadListener() {};
		virtual void OnConnected(Gamepad* pad) {};
		virtual void OnDisconnected(Gamepad* pad) {};
		virtual void OnMouseButtonUp(Gamepad* pad, int button) {};
		virtual void OnMouseButtonDown(Gamepad* pad, int button) {};
	};
}