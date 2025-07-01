#pragma once

#include "ScreenManager.h"

#include <iostream>
#include <stdexcept>

namespace sb
{
	class Application
	{
	public:
		Application();

		void update();
		void render();
		void run();

	private:
		void configureConsole();
		void initializeScreens();

	private:
		bool isRunning_{ true };
	};
}
