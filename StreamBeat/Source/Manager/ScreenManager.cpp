#include "ScreenManager.h"
#include "SongManager.h"

namespace sb
{
	ScreenManager& ScreenManager::instance()
	{
		static ScreenManager instance;
		return instance;
	}

	void ScreenManager::pushSubScreen(std::unique_ptr<Screen> screen)
	{
		screenHistory_.push(screen.get());
		tempScreens_.push_back(std::move(screen));
		activeScreen_ = screenHistory_.top();
	}

	void ScreenManager::registerScreen(std::unique_ptr<Screen> screen)
	{
		const std::string& id = screen->getID();
		if (screen && screens_.find(id) == nullptr)
		{
			screens_.insert(id, std::move(screen));
		}
	}

	void ScreenManager::navigateToRoot(const std::string& id)
	{
		std::unique_ptr<Screen>* found = screens_.find(id);
		if (found)
		{
			if (activeScreen_ && activeScreen_->getID() != ScreenNames::Temporary)
			{
				activeScreen_->resetElements();
				activeScreen_->setActive(false);
			}

			tempScreens_.clear();
			screenHistory_.clear();

			screenHistory_.push(found->get());
			activeScreen_ = screenHistory_.top();
			activeScreen_->setActive(true);
		}
	}

	void ScreenManager::goBack()
	{
		if (!screenHistory_.empty())
		{
			if (activeScreen_->getID() != ScreenNames::Temporary)
				return;

			screenHistory_.pop();
			activeScreen_ = screenHistory_.empty() ? nullptr : screenHistory_.top();
			activeScreen_->resetElements();
		}
	}

	void ScreenManager::render()
	{
		if (activeScreen_)
			activeScreen_->render();

		if (!isRestrictedScreen())
			screenBar_.render();
	}

	void ScreenManager::update()
	{
		if (activeScreen_)
			activeScreen_->update();
	}

	void ScreenManager::handleInput()
	{
		if (activeScreen_)
		{
			auto ev = Console::readInputEvent();

			if (!ev.has_value())
				return;

			if (ev->specialKey == Key::F2)
			{
				SongManager::instance().next();
			}
			
			if (ev->specialKey == Key::Tab && !isRestrictedScreen())
			{
				if (currentContext_ == NavigationContext::ScreenBar)
				{
					currentContext_ = NavigationContext::ActiveScreen;
					screenBar_.blur();
					activeScreen_->resume();
				}
				else
				{
					currentContext_ = NavigationContext::ScreenBar;
					screenBar_.focus();
					activeScreen_->suspend();
				}
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
						screenBar_.handleNavigation(*ev);
					break;
				}
			}

			if (ev->specialKey == Key::Enter && currentContext_ == NavigationContext::ScreenBar)
			{
				if (activeScreen_->getID() != screenBar_.getTargetScreen())
				{
					navigateToRoot(screenBar_.getTargetScreen());
					activeScreen_->suspend();
				}
			}
		}
	}

	void ScreenManager::setupScreenBar()
	{
		screenBar_.initialize(ScreenNames::Main);
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