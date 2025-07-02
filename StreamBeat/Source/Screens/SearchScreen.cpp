#include "SearchScreen.h"
#include "ScreenNames.h"

namespace sb
{
	SearchScreen::SearchScreen()
		: Screen(ScreenNames::Search)
	{
		onCreate();
		initializeFocus();
	}

	void SearchScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Search ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
	}

	void SearchScreen::onKeyPress(Key key)
	{

	}

	void SearchScreen::onReset()
	{

	}
}
