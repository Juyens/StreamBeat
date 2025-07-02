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
			if (found->get()->isActive())
			{
				found->get()->resetElements();
			}

			if (activeScreen_)
			{
				activeScreen_->resetElements();
				screenHistory_.push(activeScreen_);
				activeScreen_->setActive(false);
			}

			activeScreen_ = found->get();
			
			if (!activeScreen_->isActive())
				activeScreen_->setActive(true);
		}
	}

	void ScreenManager::goBack()
	{
		if (!screenHistory_.empty())
		{
			activeScreen_ = screenHistory_.peek();
			screenHistory_.pop();
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

			if (ev->specialKey == Key::Escape)
			{
				if (currentContext_ == NavigationContext::ScreenBar)
				{
					currentContext_ = NavigationContext::ActiveScreen;
					screenBar_.blur();
				}
				else 
				{
					currentContext_ = NavigationContext::ScreenBar;
					screenBar_.focus();
				}
				return;
			}

			switch (currentContext_)
			{
				case NavigationContext::ActiveScreen:
				{
					activeScreen_->handleInput(*ev);
					break;
				}
				case NavigationContext::ScreenBar:
				{
					if (!isRestrictedScreen())
						screenBar_.handlerInput(*ev);
					break;
				}
			}
		}
	}

	Screen* ScreenManager::getActiveScreen()
	{
		return activeScreen_;
	}

	bool ScreenManager::isRestrictedScreen() const
	{
		const std::string id = activeScreen_->getID();
		return id == ScreenNames::Login || id == ScreenNames::Register;
	}
}