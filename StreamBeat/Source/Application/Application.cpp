#include "Application.h"
#include "Console.h"
#include "Style.h"
#include "ScreenNames.h"
#include "LoginScreen.h"
#include "RegisterScreen.h"

#include <string>

namespace sb
{
	Application::Application()
	{
		configureConsole();
		initializeScreens();
	}

	void Application::update()
	{
		ScreenManager::instance().handleInput();
	}

	void Application::render()
	{
		Console::clearBuffer();
		ScreenManager::instance().render();
		Console::present();
	}

	void Application::run()
	{
		while (isRunning_)
		{
			update();
			render();
		}
	}

	void Application::configureConsole()
	{
		Console::applyDefaultLayout(160, 45);
		Console::setStyle(Style::TitleBar | Style::Minimize | Style::Close );
		Console::setTitle(L"𝒮𝓉𝓇ℯ𝒶𝓂𝐵ℯ𝒶𝓉");
		Console::setIcon(L"Resource/streambeat.ico");
	}

	void Application::initializeScreens()
	{
		ScreenManager::instance().registerScreen(std::make_unique<LoginScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<RegisterScreen>());
		ScreenManager::instance().setActive(ScreenNames::Login);
	}
}