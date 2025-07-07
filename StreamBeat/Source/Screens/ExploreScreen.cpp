#include "ExploreScreen.h"
#include "ScreenNames.h"

namespace sb
{
	ExploreScreen::ExploreScreen()
		: Screen(ScreenNames::Explore)
	{
		onCreate();
		initializeFocus();
	}

	void ExploreScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 1;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Explore ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);
		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Explore ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);

		tableView_ = addElement<TableView<Song>>();
		tableView_->setGridSize({ 2, 20 });
		tableView_->centerX(consoleSize.x());
		tableView_->setY(baseY + 2);

		refreshRecommendations();
	}

	void ExploreScreen::onKeyPress(Key key)
	{

	}

	void ExploreScreen::onReset()
	{
		refreshRecommendations();
	}

	void ExploreScreen::refreshRecommendations()
	{
		auto items = RecommendationManager::instance().getRecommendations();
		tableView_->setItems(items);
	}
}
