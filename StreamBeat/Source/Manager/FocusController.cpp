#include "FocusController.h"
#include <cmath>
#include <limits>

namespace sb 
{
	void FocusController::setInteractives(const std::vector<Interactive*>& interactives)
	{
		interactives_ = interactives;
		current_ = nullptr;
	}

	void FocusController::focusFirst() 
	{
		if (!interactives_.empty()) {
			current_ = interactives_.front();
			current_->setFocus(true);
		}
	}

	void FocusController::handleNavigation(Key key) 
	{
		if (!current_) return;

		Interactive* next = findClosestInDirection(key);
		if (next && next != current_) 
		{
			current_->setFocus(false);
			next->setFocus(true);
			current_ = next;
		}
	}

	sb::Interactive* FocusController::getCurrent() const
	{
		return current_;
	}

	Interactive* FocusController::findClosestInDirection(Key key)
	{
		if (!current_) return nullptr;

		const auto currentPos = current_->getPosition();
		Interactive* closest = nullptr;
		double minDistance = std::numeric_limits<double>::max();

		for (auto* target : interactives_) 
		{
			if (target == current_) continue;

			const auto targetPos = target->getPosition();
			int dx = targetPos.x() - currentPos.x();
			int dy = targetPos.y() - currentPos.y();

			bool inDirection = false;
			switch (key) 
			{
			case Key::Up:    inDirection = (dy < 0); break;
			case Key::Down:  inDirection = (dy > 0); break;
			case Key::Left:  inDirection = (dx < 0); break;
			case Key::Right: inDirection = (dx > 0); break;
			}

			if (!inDirection) continue;

			double distance = std::hypot(dx, dy);
			if (distance < minDistance) 
			{
				minDistance = distance;
				closest = target;
			}
		}

		return closest;
	}

}
