#include "SearchScreen.h"
#include "ScreenNames.h"
#include "SubSearchScreen.h"
#include "ScreenManager.h"
#include "Artist.h"

#include <memory>

namespace sb
{
	SearchScreen::SearchScreen()
		: Screen(ScreenNames::Search)
	{
		onCreate();
		initializeFocus();
	}

	void SearchScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 5;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Search ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(1);

		searchArtistBt_ = addElement<Button>();
		searchArtistBt_->setText("Buscar Artista");
		searchArtistBt_->centerX(consoleSize.x());
		searchArtistBt_->setY(baseY + 2);

		searchArtistBt_->setOnEnter([]
			{
				ScreenManager::instance().pushSubScreen(std::make_unique<SubSearchScreen<Artist>>("Artist"));
			});

		searchAlbumBt_ = addElement<Button>();
		searchAlbumBt_->setText("Buscar Album");
		searchAlbumBt_->centerX(consoleSize.x());
		searchAlbumBt_->setY(baseY + 6);

		searchAlbumBt_->setOnEnter([]
			{
				ScreenManager::instance().pushSubScreen(std::make_unique<SubSearchScreen<Album>>("Album"));
			});

		searchSongBt_ = addElement<Button>();
		searchSongBt_->setText("Buscar Cancion");
		searchSongBt_->centerX(consoleSize.x());
		searchSongBt_->setY(baseY + 10);

		searchSongBt_->setOnEnter([]
			{
				ScreenManager::instance().pushSubScreen(std::make_unique<SubSearchScreen<Song>>("Song"));
			});

		searchMostDurationBtn_ = addElement<Button>();
		searchMostDurationBtn_->setText("Mayor reproducciones");
		searchMostDurationBtn_->centerX(consoleSize.x());
		searchMostDurationBtn_->setY(baseY + 14);
		searchMostDurationBtn_->setOnEnter([this] {
			auto songs = DataManager::instance().getSongsByDuration(false);
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Song>>("[ Mayor duracion >> Songs ]", songs, [] (std::shared_ptr<Song> target) {
					ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
					}));
			});

		searchLeastDurationBtn_ = addElement<Button>();
		searchLeastDurationBtn_->setText("Menor reproducciones");
		searchLeastDurationBtn_->centerX(consoleSize.x());
		searchLeastDurationBtn_->setY(baseY + 18);
		searchLeastDurationBtn_->setOnEnter([this] {
			auto songs = DataManager::instance().getSongsByDuration(true);
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Song>>("[ Menor duracion >> Songs ]", songs, [] (std::shared_ptr<Song> target) {
					ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
					}));
			});

		searchMostPlaysBtn_ = addElement<Button>();
		searchMostPlaysBtn_->setText("Mayor visualizacion");
		searchMostPlaysBtn_->centerX(consoleSize.x());
		searchMostPlaysBtn_->setY(baseY + 22);
		searchMostPlaysBtn_->setOnEnter([this] {
			auto songs = DataManager::instance().getSongsByReproductions(false);
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Song>>("[ Mayor visualizacion >> Songs ]", songs, [] (std::shared_ptr<Song> target) {
					ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
					}));
			});

		searchLeastPlaysBtn_ = addElement<Button>();
		searchLeastPlaysBtn_->setText("Menor visualizacion");
		searchLeastPlaysBtn_->centerX(consoleSize.x());
		searchLeastPlaysBtn_->setY(baseY + 26);
		searchLeastPlaysBtn_->setOnEnter([this] {
			auto songs = DataManager::instance().getSongsByReproductions(true);
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Song>>("[ Menor visualizacion >> Songs ]", songs, [] (std::shared_ptr<Song> target) {
					ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
					}));
			});
	}

	void SearchScreen::onKeyPress(Key key)
	{

	}

	void SearchScreen::onReset()
	{

	}
}
