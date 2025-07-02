#include "ScreenBar.h"
#include "UserManager.h"
#include "Utils.h"

namespace sb
{
	void ScreenBar::initialize(const std::string& id)
	{
		if (!interactives_.empty())
			interactives_.clear();

		if (!screenMap_.empty())
			screenMap_.clear();

		onCreate();

		auto found = screenMap_.find(id);
		if (found)
		{
			current_ = *found;
		}
	}

	void ScreenBar::render()
	{
		for (const auto& target : interactives_)
		{
			target->render();
		}
	}

	void ScreenBar::handleNavigation(const InputEvent& ev)
	{
		if (!current_) return;

		if (current_->wantsExclusiveInput())
			return;

		ScreenButton* next = findClosestHorizontal(*ev.specialKey);
		if (next && next != current_)
		{
			current_->setFocus(false);
			current_ = next;
			current_->setFocus(true);
		}

		if (*ev.specialKey == Key::Enter)
		{
			targetScreen_ = current_->getTargetScreen();
		}
	}

	void ScreenBar::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = consoleSize.y() - 5;
		const int paddingX = 2;

		if (UserManager::instance().getCurrentUser().getPlan() == "Artista")
		{
			music_ = addElement(ScreenNames::Music);
			music_->setText("Mi Musica");
		}

		main_ = addElement(ScreenNames::Main);
		main_->setText("Inicio");

		explore_ = addElement(ScreenNames::Explore);
		explore_->setText("Explorar");

		profile_ = addElement(ScreenNames::Profile);
		profile_->setText("Perfil");

		library_ = addElement(ScreenNames::Library);
		library_->setText("Biblioteca");

		history_ = addElement(ScreenNames::History);
		history_->setText("Historial");

		search_ = addElement(ScreenNames::Search);
		search_->setText("Buscar");

		const int totalWidth = ((music_) ? music_->getWidth() : 0) + main_->getWidth() + explore_->getWidth() 
			+ profile_->getWidth() + library_->getWidth() + history_->getWidth() + search_->getWidth() + paddingX * static_cast<int>(interactives_.size());

		const int baseX = utils::centered(consoleSize.x(), totalWidth);

		interactives_[0]->setX(baseX);
		interactives_[0]->setY(baseY);

		for (uint i = 1; i < interactives_.size(); ++i)
		{
			int posX = interactives_[i - 1]->getX() + interactives_[i - 1]->getWidth() + paddingX;
			interactives_[i]->setY(baseY);
			interactives_[i]->setX(posX);
		}
	}

	ScreenButton* ScreenBar::findClosestHorizontal(Key key)
	{
		if (!current_) return nullptr;

		if (key != Key::Left && key != Key::Right)
			return nullptr;

		const auto currentPos = current_->getPosition();
		const auto currentSize = current_->getSize();

		const int currLeft = currentPos.x();
		const int currTop = currentPos.y();
		const int currRight = currLeft + currentSize.x() - 1;
		const int currBottom = currTop + currentSize.y() - 1;

		ScreenButton* closest = nullptr;
		double minDistance = std::numeric_limits<double>::max();

		for (const auto& target : interactives_)
		{
			if (target.get() == current_ || !target->isVisible()) continue;

			const auto pos = target->getPosition();
			const auto size = target->getSize();

			const int left = pos.x();
			const int top = pos.y();
			const int right = left + size.x() - 1;
			const int bottom = top + size.y() - 1;

			bool valid = false;

			switch (key)
			{
			case Key::Left:
				valid = (right < currLeft) && !(bottom < currTop || top > currBottom);
				break;
			case Key::Right:
				valid = (left > currRight) && !(bottom < currTop || top > currBottom);
				break;
			default:
				break;
			}

			if (!valid) continue;

			Vector2i centerTarget{ left + size.x() / 2, top + size.y() / 2 };
			Vector2i centerCurrent{ currLeft + currentSize.x() / 2, currTop + currentSize.y() / 2 };

			double distance = std::hypot(centerTarget.x() - centerCurrent.x(), centerTarget.y() - centerCurrent.y());
			if (distance < minDistance)
			{
				minDistance = distance;
				closest = target.get();
			}
		}

		return closest;
	}

	void ScreenBar::focus()
	{
		if (current_)
		{
			current_->activate();
			current_->focus();
			hasFocus_ = true;
		}
	}

	void ScreenBar::blur()
	{
		if (current_)
		{
			current_->deactivate();
			hasFocus_ = false;
		}
	}

	bool ScreenBar::hasFocus() const
	{
		return hasFocus_;
	}

	const std::string& ScreenBar::getTargetScreen() const
	{
		return targetScreen_;
	}

	void ScreenBar::clearTargetScreen()
	{
		targetScreen_ = ScreenNames::None;
	}
}
