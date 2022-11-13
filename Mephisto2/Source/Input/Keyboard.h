#pragma once
#include <memory>
#include <vector>
class IKeyboardListener;

namespace ME::Input {
	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();
		static std::shared_ptr<Keyboard> Get();
		void AddListener(IKeyboardListener* listener);
		void RemoveListener(IKeyboardListener* listener);
	private:
		static std::shared_ptr<Keyboard> GKeyboard;
		std::vector<IKeyboardListener*> Listeners;
	};
}
