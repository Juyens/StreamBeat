#pragma once

#include "SubScreen.h"
#include "UI.h"
#include "Console.h"
#include "Artist.h"
#include "ScreenManager.h"
#include "SubListScreen.h"
#include "SubAlbumScreen.h"
#include "SubSongScreen.h"

#include <memory>

namespace sb
{
	class SubArtistScreen : public SubScreen
	{
	public:
		SubArtistScreen(std::shared_ptr<Artist> artist)
			: artist_(artist)
		{
			onCreate();
			initializeFocus();
		}

		void update() override
		{

		}

	protected:
		void onCreate() override
		{
			const auto consoleSize = Console::getViewportSize();
			const int baseY = 3;

			titleLb_ = addElement<Label>();
			titleLb_->setText("[ StreamBeat - Artist >> " + artist_->getName() + " ]");
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);

			listAlbumsBt_ = addElement<Button>();
			listAlbumsBt_->setText("Listar Albumes");
			listAlbumsBt_->centerX(consoleSize.x());
			listAlbumsBt_->setY(baseY + 5);
			listAlbumsBt_->setOnEnter([this] {
				auto albums = DataManager::instance().getAlbumsByArtist(artist_->getName());
				ScreenManager::instance().pushSubScreen(
					std::make_unique<SubListScren<Album>>("[ " + artist_->getName() + " >> Albums ]", albums, [] (std::shared_ptr<Album> target) {
						ScreenManager::instance().pushSubScreen(std::make_unique<SubAlbumScreen>(target));
						}));
				});

			listSongsBt_ = addElement<Button>();
			listSongsBt_->setText("Listar canciones");
			listSongsBt_->centerX(consoleSize.x());
			listSongsBt_->setY(baseY + 10);
			listSongsBt_->setOnEnter([this] {
				auto songs = DataManager::instance().getSongsByArtist(artist_->getName());
				ScreenManager::instance().pushSubScreen(
					std::make_unique<SubListScren<Song>>("[ " + artist_->getName() + " >> Songs ]", songs, [] (std::shared_ptr<Song> target) {
						ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
						}));
				});

			addLibraryBt_ = addElement<Button>();
			addLibraryBt_->setText("Agregar a la Biblioteca");
			addLibraryBt_->centerX(consoleSize.x());
			addLibraryBt_->setY(baseY + 15);

			backBt_ = addElement<Button>();
			backBt_->setText("Volver");
			backBt_->centerX(consoleSize.x());
			backBt_->setY(baseY + 20);
			backBt_->setOnEnter([] { ScreenManager::instance().goBack(); });
		}

		void onKeyPress(Key key) override
		{
			if (auto* focused = focusController_.getCurrent())
			{
				if (focused->wantsExclusiveInput())
					return;
			}

			if (key == Key::Escape)
			{
				ScreenManager::instance().goBack();
			}
		}

		void onReset() override
		{

		}

	private:
		std::shared_ptr<Artist> artist_;
		Button* listAlbumsBt_{ nullptr };
		Button* listSongsBt_{ nullptr };
		Button* addLibraryBt_{ nullptr };
		Button* backBt_{ nullptr };
	};
}