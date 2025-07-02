#include "ExploreScreen.h"
#include "ScreenNames.h"

namespace sb
{
	ExploreScreen::ExploreScreen()
		: Screen(ScreenNames::Explore)
	{
		onCreate();
		initializeFocus();
	}

	void ExploreScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Explore ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
	}

	void ExploreScreen::onKeyPress(Key key)
	{

	}

	void ExploreScreen::onReset()
	{
	}
}
