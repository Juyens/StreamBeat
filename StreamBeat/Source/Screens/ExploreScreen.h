#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"
#include "TableView.h"
#include "RecommendationManager.h"

namespace sb
{
	class ExploreScreen : public Screen
	{
	public:
		ExploreScreen();

	protected:
		void onCreate() override;
		void onKeyPress(Key key) override;
		void onReset() override;

	private:
		Label* titleLb_{ nullptr };
		TableView<Song>* tableView_{ nullptr };
		void refreshRecommendations();
	};
}