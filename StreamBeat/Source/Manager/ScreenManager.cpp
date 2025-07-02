#include "ScreenManager.h"

namespace sb
{
	ScreenManager& ScreenManager::instance()
	{
		static ScreenManager instance;
		return instance;
	}

	void ScreenManager::registerScreen(std::unique_ptr<Screen> screen)
	{
		const std::string& id = screen->getID();
		if (screen && screens_.find(id) == nullptr)
		{
			screens_.insert(id, std::move(screen));
		}
	}

	void ScreenManager::setActive(const std::string& id)
	{
		std::unique_ptr<Screen>* found = screens_.find(id);
		if (found)
		{
			activeScreen_ = found->get();
		}
	}

	void ScreenManager::render()
	{
		if (activeScreen_)
			activeScreen_->render();
	}

	void ScreenManager::handleInput()
	{
		if (activeScreen_)
		{
			auto ev = Console::readInputEvent();

			if (!ev.has_value()) 
				return;

			activeScreen_->handleInput(*ev);
		}
			
	}

	Screen* ScreenManager::getActiveScreen()
	{
		return activeScreen_;
	}
}