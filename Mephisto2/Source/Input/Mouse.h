#include "IMouseListener.h"
#include <vector>
#include <memory>
namespace ME::Input
{
	class Mouse
	{
	public:
		enum MouseButton
		{
			Left = 1,
			Right = 3,
			Middle = 2,
			X1 = 4,
			WheelUp,
			WheelDown,
			X2,
			NumberOfButtons
		};

		Mouse();
		static std::shared_ptr<Mouse> Get();
		virtual ~Mouse() {};
		virtual void Show();
		virtual void Hide();
		virtual bool SetVisibility(bool bShowCursor);
		virtual Vec2<float> GetPos() const;
		virtual bool IsDown(int button) const;
		virtual bool IsUp(int button) const;

		void OnStartFrame();
		void AddListener(IMouseListener* listener);
		void RemoveListener(IMouseListener* listener);

		void TriggerMoveEvent(const Vec2<float>& position);
		void TriggerButtonDownEvent(const Vec2<float>& position, int button);
		void TriggerButtonUpEvent(const Vec2<float>& position, int button);
		void TriggerScrollwheelEvent(const Vec2<float>& position, const Vec2<float>& ScrollAmount);

	private:

		static std::shared_ptr<Mouse> GMouse;
		bool bIsVisible;
		Vec2<float> Position;
		std::vector<IMouseListener*> Listeners;
		std::vector<bool> ButtonsDown;
		std::vector<bool> ButtonsJustDown;
		std::vector<bool> ButtonsJustUp;
	};
};