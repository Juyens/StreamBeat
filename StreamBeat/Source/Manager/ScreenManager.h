#pragma once

#include "Screen.h"
#include "HashTable.h"
#include "Stack.h"
#include "ScreenBar.h"

#include <memory>
#include <string>

namespace sb
{
	enum class NavigationContext
	{
		ActiveScreen,
		ScreenBar
	};

	class ScreenManager
	{
	public:
		static ScreenManager& instance();

		void registerScreen(std::unique_ptr<Screen> screen);
		void setActive(const std::string& id);
		void goBack();

		void render();
		void handleInput();
		void setupScreenBar();

		Screen* getActiveScreen();

	private:
		bool isRestrictedScreen() const;

	private:
		ScreenManager() = default;
		ScreenManager(const ScreenManager&) = delete;
		ScreenManager& operator=(const ScreenManager&) = delete;
		HashTable<std::string, std::unique_ptr<Screen>> screens_;
		Screen* activeScreen_ = nullptr;
		Stack<Screen*> screenHistory_;
		NavigationContext currentContext_ = NavigationContext::ActiveScreen;
		ScreenBar screenBar_;
	};
}