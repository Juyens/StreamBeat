#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"
#include "TableView.h"
#include "RecommendationManager.h"
#include "DataManager.h"
#include "SongManager.h"

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
		void update() override;

	private:
		Label* titleLb_{ nullptr };
		TableView<Song>* tableView_{ nullptr };
		void refreshRecommendations();
		bool recommendationsLoaded_{ false };
		uint prevHistorySize_{ 0 };
	};
}