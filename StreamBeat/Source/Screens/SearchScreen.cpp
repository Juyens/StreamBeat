#include "SearchScreen.h"
#include "ScreenNames.h"

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

		searchAlbumBt_ = addElement<Button>();
		searchAlbumBt_->setText("Buscar Album");
		searchAlbumBt_->centerX(consoleSize.x());
		searchAlbumBt_->setY(baseY + 10);

		searchSongBt_ = addElement<Button>();
		searchSongBt_->setText("Buscar Cancion");
		searchSongBt_->centerX(consoleSize.x());
		searchSongBt_->setY(baseY + 15);
	}

	void SearchScreen::onKeyPress(Key key)
	{

	}

	void SearchScreen::onReset()
	{

	}
}
