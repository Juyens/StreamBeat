#pragma once

#include "Interactive.h"
#include "List.h"

namespace sb 
{
	class FocusController 
	{
	public:
		void setInteractives(List<Interactive*>& interactives);
		void focusFirst();
		void handleNavigation(Key key);
		Interactive* getCurrent() const;

	private:
		Interactive* findClosestInDirection(Key direction);

	private:
		Interactive* current_ = nullptr;
		List<Interactive*> interactives_;
	};
}