#include <Core/IApplication.h>
#include <Input/IMouseListener.h>
#include <Input/IKeyboardListener.h>
#include <Graphics/IWindow.h>

class App : public IApplication, public ME::Input::IMouseListener, ME::Input::IKeyboardListener
{
	void Tick(float DeltaSeconds) override;
	void PreInit() override;
};

