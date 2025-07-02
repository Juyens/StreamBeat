#include "ProfileScreen.h"
#include "ScreenNames.h"

namespace sb
{
	ProfileScreen::ProfileScreen()
		: Screen(ScreenNames::Profile)
	{
		onCreate();
		initializeFocus();
	}

	void ProfileScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Profile ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
	}

	void ProfileScreen::onKeyPress(Key key)
	{

	}

	void ProfileScreen::onReset()
	{

	}
}
