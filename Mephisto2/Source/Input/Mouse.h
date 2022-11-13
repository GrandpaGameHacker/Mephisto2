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
			Left,
			Right,
			Middle,
			WheelUp,
			WheelDown,
			X1, X2,
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

	private:

		static std::shared_ptr<Mouse> GMouse;
		bool bIsVisible;
		Vec2<float> Position;
		std::vector<IMouseListener*> Listeners;
		std::vector<bool> ButtonsDown;
		std::vector<bool> ButtonsUp;
	};
};