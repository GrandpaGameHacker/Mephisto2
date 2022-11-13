#include <Core/IApplication.h>
#include <Input/IMouseListener.h>
#include <Input/IKeyboardListener.h>
class App : public IApplication, public ME::Input::IMouseListener, ME::Input::IKeyboardListener
{
	void Tick(float DeltaSeconds) override;
	void PreInit() override;
	void OnMouseButtonDown(const Vec2<float>& position, int button) override;
	void OnKeyDown(int key) override;
	void OnMouseWheel(const Vec2<float>& position, const Vec2<float>& ScrollAmount);
};