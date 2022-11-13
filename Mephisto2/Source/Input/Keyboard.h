#pragma once
#include <memory>
#include <vector>
#include <Input/IKeyboardListener.h>

namespace ME::Input {
	enum SDL_SPECIAL
	{
		RSHIFT = 303,
		LSHIFT = 304,
		RCTRL = 305,
		LCTRL = 306,
		RALT = 307,
		LALT = 308,
	};

	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();
		void OnStartFrame();
		static std::shared_ptr<Keyboard> Get();
		void AddListener(IKeyboardListener* listener);
		void RemoveListener(IKeyboardListener* listener);

		void SetKeyDown(int key, bool bDown);

		bool IsKeyDown(int button) const;
		bool IsKeyJustDown(int button) const;
		bool IsKeyJustUp(int button) const;

		bool IsShiftDown();
		bool IsAltDown();
		bool IsCtrlDown();

		bool IsLeftShiftDown();
		bool IsRightShiftDown();
		bool IsLeftAltDown();
		bool IsRightAltDown();
		bool IsLeftCtrlDown();
		bool IsRightCtrlDown();

		bool IsCapslockEnabled();
		bool IsNumlockEnabled();
		bool IsScrollLockEnabled();

		void TriggerKeyDownEvent(int button);
		void TriggerKeyUpEvent(int button);

	private:
		static std::shared_ptr<Keyboard> GKeyboard;

		std::vector<IKeyboardListener*> Listeners;

		std::vector<bool> KeysDown;
		std::vector<bool> KeysJustUp;
		std::vector<bool> KeysJustDown;
	};
}
