#include "LibraryScreen.h"
#include "ScreenNames.h"

namespace sb
{
	LibraryScreen::LibraryScreen()
		: Screen(ScreenNames::Library)
	{
		onCreate();
		initializeFocus();
	}

	void LibraryScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Library ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
	}

	void LibraryScreen::onKeyPress(Key key)
	{

	}

	void LibraryScreen::onReset()
	{

	}
}
