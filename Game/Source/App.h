#include <Core/IApplication.h>
#include <Input/IMouseListener.h>
class App : public IApplication, public ME::Input::IMouseListener
{
	void Tick(float DeltaSeconds) override;
	void PreInit() override;
	void OnMouseButtonDown(const Vec2<float>& position, int button) override;
};