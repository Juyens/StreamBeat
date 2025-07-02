#include "MainScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"
#include "Utils.h"

namespace sb
{
	MainScreen::MainScreen()
		: Screen(ScreenNames::Main)
	{
		onCreate();
		initializeFocus();
	}

	void MainScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Main]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);


	}

	void MainScreen::onKeyPress(Key key)
	{
		if (key == Key::Escape)
		{
			UserManager::instance().logout();
			ScreenManager::instance().setActive(ScreenNames::Login);
		}
	}

	void MainScreen::onReset()
	{
		
	}
}
