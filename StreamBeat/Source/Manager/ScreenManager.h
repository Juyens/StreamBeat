#pragma once

#include "Screen.h"
#include "HashTable.h"
#include "Stack.h"
#include "ScreenBar.h"
#include "List.h"

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

		void pushSubScreen(std::unique_ptr<Screen> screen);
		void registerScreen(std::unique_ptr<Screen> screen);
		void navigateToRoot(const std::string& id);
		void goBack();

		void update();
		void render();
		void handleInput();
		void setupScreenBar();

		Screen* getActiveScreen();

	private:
		ScreenManager() = default;
		ScreenManager(const ScreenManager&) = delete;

		ScreenManager& operator=(const ScreenManager&) = delete;

		bool isRestrictedScreen() const;

	private:
		HashTable<std::string, std::unique_ptr<Screen>> screens_;
		List<std::unique_ptr<Screen>> tempScreens_;
		Stack<Screen*> screenHistory_;

		Screen* activeScreen_{ nullptr };

		ScreenBar screenBar_;
		NavigationContext currentContext_ = NavigationContext::ActiveScreen;
	};
}