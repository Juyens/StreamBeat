#pragma once

#include "Interactive.h"
#include <vector>

namespace sb 
{
	class FocusController 
	{
	public:
		void setInteractives(const std::vector<Interactive*>& interactives);
		void focusFirst();
		void handleNavigation(Key key);
		Interactive* getCurrent() const;

	private:
		Interactive* current_ = nullptr;
		std::vector<Interactive*> interactives_;

		Interactive* findClosestInDirection(Key direction);
	};
}