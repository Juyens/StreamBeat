#include "HistoryScreen.h"
#include "ScreenNames.h"

namespace sb
{
	HistoryScreen::HistoryScreen()
		: Screen(ScreenNames::History)
	{
		onCreate();
		initializeFocus();
	}

	void HistoryScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - History ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
	}

	void HistoryScreen::onKeyPress(Key key)
	{

	}

	void HistoryScreen::onReset()
	{
	}
}
