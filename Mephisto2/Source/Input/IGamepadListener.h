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
		virtual void OnButtonUp(Gamepad* pad, int button) {};
		virtual void OnButtonDown(Gamepad* pad, int button) {};
	};
}