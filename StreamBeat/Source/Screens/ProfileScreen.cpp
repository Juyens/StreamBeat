#include "ProfileScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"

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
		const int baseY = 7;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Profile ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(1);

		viewInfo = addElement<Button>();
		viewInfo->setText("Ver Informacion General");
		viewInfo->centerX(consoleSize.x());
		viewInfo->setY(baseY);

		changePass = addElement<Button>();
		changePass->setText("Cambiar clave");
		changePass->centerX(consoleSize.x());
		changePass->setY(baseY + 5);

		changeUser = addElement<Button>();
		changeUser->setText("Cambiar nombre de Usuario");
		changeUser->centerX(consoleSize.x());
		changeUser->setY(baseY + 10);

		changePlan = addElement<Button>();
		changePlan->setText("Cambiar Plan");
		changePlan->centerX(consoleSize.x());
		changePlan->setY(baseY + 15);
	}

	void ProfileScreen::onKeyPress(Key key)
	{

	}

	void ProfileScreen::onReset()
	{

	}
}
