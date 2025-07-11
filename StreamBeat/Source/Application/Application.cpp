﻿#include "Application.h"

#include "Console.h"
#include "Style.h"
#include "ScreenNames.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"
#include "MusicScreen.h"
#include "MainScreen.h"
#include "ExploreScreen.h"
#include "ProfileScreen.h"
#include "LibraryScreen.h"
#include "HistoryScreen.h"
#include "SearchScreen.h"
#include "SongManager.h"

#include <string>

namespace sb
{
	Application::Application()
	{
		configureConsole();
		setup();
	}

	void Application::update()
	{
		ScreenManager::instance().handleInput();
		ScreenManager::instance().update();
	}

	void Application::render()
	{
		Console::clearBuffer();
		ScreenManager::instance().render();
		SongManager::instance().show();
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

	void Application::setup()
	{
		DataManager::instance().loadAsync();
		// -------------------------------------------- //

		ScreenManager::instance().registerScreen(std::make_unique<LoginScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<RegisterScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<MusicScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<MainScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<ExploreScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<ProfileScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<LibraryScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<HistoryScreen>());
		ScreenManager::instance().registerScreen(std::make_unique<SearchScreen>());

		// -------------------------------------------- //

		ScreenManager::instance().navigateToRoot(ScreenNames::Login);
	}
}