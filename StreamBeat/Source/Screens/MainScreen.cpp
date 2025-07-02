#include "MainScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"
#include "Utils.h"
#include "Drawing.h"

namespace sb
{
	MainScreen::MainScreen()
		: Screen(ScreenNames::Main)
	{
		onCreate();
		initializeFocus();
	}

	void MainScreen::onRender()
	{
		Drawing::drawArt(utils::centered(Console::getViewportSize().x(), 94), utils::centered(Console::getViewportSize().y(), 8) - 5, art::TITLE, PalettePresets::Default);
	}

	void MainScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Main ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);

		logoutButton_ = addElement<Button>();
		logoutButton_->setText("Cerrar sesion");
		logoutButton_->centerX(consoleSize.x());
		logoutButton_->setY(baseY + 25);
		logoutButton_->setOnEnter([] { UserManager::instance().logout(); ScreenManager::instance().setActive(ScreenNames::Login); });
	}

	void MainScreen::onKeyPress(Key key)
	{

	}

	void MainScreen::onReset()
	{
		
	}
}
