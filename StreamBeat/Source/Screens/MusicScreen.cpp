#include "MusicScreen.h"
#include "ScreenNames.h"

namespace sb
{
	MusicScreen::MusicScreen()
		: Screen(ScreenNames::Music)
	{
		onCreate();
		initializeFocus();
	}

	void MusicScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Music]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
	}

	void MusicScreen::onKeyPress(Key key)
	{

	}

	void MusicScreen::onReset()
	{

	}
}