#include "FocusController.h"

#include <cmath>
#include <limits>

namespace sb 
{
	void FocusController::setInteractives(List<Interactive*>& interactives)
	{
		interactives_ = std::move(interactives);
		current_ = nullptr;
	}

	void FocusController::focusFirst() 
	{
		if (!interactives_.empty()) 
		{
			if (current_)
				current_->blur();

			current_ = interactives_.front();
			current_->setFocus(true);
		}
	}

	void FocusController::handleNavigation(Key key) 
	{
		if (!current_) return;

		if (current_->wantsExclusiveInput())
			return;

		Interactive* next = findClosestInDirection(key);
		if (next && next != current_) 
		{
			current_->setFocus(false);
			next->setFocus(true);
			current_ = next;
		}
	}

	Interactive* FocusController::getCurrent() const
	{
		return current_;
	}

	Interactive* FocusController::findClosestInDirection(Key key)
	{
		if (!current_) return nullptr;

		const auto currentPos = current_->getPosition();
		const auto currentSize = current_->getSize();

		const int currLeft = currentPos.x();
		const int currTop = currentPos.y();
		const int currRight = currLeft + currentSize.x() - 1;
		const int currBottom = currTop + currentSize.y() - 1;

		Interactive* closest = nullptr;
		double minDistance = std::numeric_limits<double>::max();

		for (auto* target : interactives_)
		{
			if (target == current_ || !target->isVisible()) continue;

			const auto pos = target->getPosition();
			const auto size = target->getSize();

			const int left = pos.x();
			const int top = pos.y();
			const int right = left + size.x() - 1;
			const int bottom = top + size.y() - 1;

			bool valid = false;

			switch (key) {
			case Key::Up:
				valid = (bottom < currTop) && !(right < currLeft || left > currRight);
				break;
			case Key::Down:
				valid = (top > currBottom) && !(right < currLeft || left > currRight);
				break;
			case Key::Left:
				valid = (right < currLeft) && !(bottom < currTop || top > currBottom);
				break;
			case Key::Right:
				valid = (left > currRight) && !(bottom < currTop || top > currBottom);
				break;
			}

			if (!valid) continue;

			Vector2i centerTarget{ left + size.x() / 2, top + size.y() / 2 };
			Vector2i centerCurrent{ currLeft + currentSize.x() / 2, currTop + currentSize.y() / 2 };

			double distance = std::hypot(centerTarget.x() - centerCurrent.x(), centerTarget.y() - centerCurrent.y());
			if (distance < minDistance) {
				minDistance = distance;
				closest = target;
			}
		}

		return closest;
	}
}
