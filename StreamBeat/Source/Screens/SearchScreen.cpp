#include "SearchScreen.h"
#include "ScreenNames.h"
#include "SubSearchScreen.h"
#include "ScreenManager.h"
#include "Artist.h"

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
		const int baseY = 8;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Search ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(1);

		searchArtistBt_ = addElement<Button>();
		searchArtistBt_->setText("Buscar Artista");
		searchArtistBt_->centerX(consoleSize.x());
		searchArtistBt_->setY(baseY + 5);

		searchArtistBt_->setOnEnter([] 
			{
				ScreenManager::instance().pushSubScreen(std::make_unique<SubSearchScreen<Artist>>("Artist"));
			});

		searchAlbumBt_ = addElement<Button>();
		searchAlbumBt_->setText("Buscar Album");
		searchAlbumBt_->centerX(consoleSize.x());
		searchAlbumBt_->setY(baseY + 10);

		searchAlbumBt_->setOnEnter([]
			{
				ScreenManager::instance().pushSubScreen(std::make_unique<SubSearchScreen<Album>>("Album"));
			});

		searchSongBt_ = addElement<Button>();
		searchSongBt_->setText("Buscar Cancion");
		searchSongBt_->centerX(consoleSize.x());
		searchSongBt_->setY(baseY + 15);

		searchSongBt_->setOnEnter([]
			{
				ScreenManager::instance().pushSubScreen(std::make_unique<SubSearchScreen<Song>>("Song"));
			});
	}

	void SearchScreen::onKeyPress(Key key)
	{

	}

	void SearchScreen::onReset()
	{

	}
}
