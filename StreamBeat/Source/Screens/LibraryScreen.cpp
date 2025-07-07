#include "LibraryScreen.h"
#include "ScreenNames.h"
#include "SubListScreen.h"
#include "DataManager.h"
#include "UserManager.h"
#include "ScreenManager.h"
#include "SubArtistScreen.h"
#include "SubAlbumScreen.h"
#include "SubSongScreen.h"
#include "SubPlaylistScreen.h"

#include <memory>

namespace sb
{
	LibraryScreen::LibraryScreen()
		: Screen(ScreenNames::Library)
	{
		onCreate();
		initializeFocus();
	}

	void LibraryScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 4;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Library ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(1);

		listArtistBt_ = addElement<Button>();
		listArtistBt_->setText("Mis Artistas");
		listArtistBt_->centerX(consoleSize.x());
		listArtistBt_->setY(baseY + 5);
		listArtistBt_->setOnEnter([this] {
			auto artist = UserManager::instance().getCurrentLibrary().getArtists();
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Artist>>("[ Library >> Artist ]", artist, [] (std::shared_ptr<Artist> target) {
					ScreenManager::instance().pushSubScreen(std::make_unique<SubArtistScreen>(target));
					}));
			});

		listAlbumsBt_ = addElement<Button>();
		listAlbumsBt_->setText("Mis Albums");
		listAlbumsBt_->centerX(consoleSize.x());
		listAlbumsBt_->setY(baseY + 10);
		listAlbumsBt_->setOnEnter([this] {
			auto albums = UserManager::instance().getCurrentLibrary().getAlbums();
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Album>>("[ Library >> Albums ]", albums, [] (std::shared_ptr<Album> target) {
					ScreenManager::instance().pushSubScreen(std::make_unique<SubAlbumScreen>(target));
					}));
			});

		listPlayListBt_ = addElement<Button>();
		listPlayListBt_->setText("Mis PlayList");
		listPlayListBt_->centerX(consoleSize.x());
		listPlayListBt_->setY(baseY + 15);
		listPlayListBt_->setOnEnter([this] {
			auto playlists = UserManager::instance().getCurrentLibrary().getPlaylists();
			ScreenManager::instance().pushSubScreen(
				std::make_unique<SubListScreen<Playlist>>(
					"[ Library >> Playlist ]",
					playlists,
					[] (std::shared_ptr<Playlist> selectedPlaylist) {
						ScreenManager::instance().pushSubScreen(
							std::make_unique<SubPlaylistScreen>(selectedPlaylist)
						);
					}
				)
			);
			});

		texBox_ = addElement<TextBox>();
		texBox_->centerX(consoleSize.x());
		texBox_->setY(baseY + 20);

		addPlaylistBt_ = addElement<Button>();
		addPlaylistBt_->setText("Agregar Playlist");
		addPlaylistBt_->centerX(consoleSize.x());
		addPlaylistBt_->setY(baseY + 23);
		addPlaylistBt_->setOnEnter([this] { 
			if (!texBox_->getText().empty())
			{
				UserManager::instance().getCurrentLibrary().addPlaylist(texBox_->getText());
				texBox_->reset();
			}
			});

		backLb_ = addElement<Button>();
		backLb_->setText("Volver");
		backLb_->centerX(consoleSize.x());
		backLb_->setY(baseY + 28);
		backLb_->setOnEnter([] {
			ScreenManager::instance().goBack();
			});
	}

	void LibraryScreen::onKeyPress(Key key)
	{

	}

	void LibraryScreen::onReset()
	{

	}
}
