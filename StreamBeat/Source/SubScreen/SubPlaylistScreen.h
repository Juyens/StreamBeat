#pragma once

#include "SubScreen.h"
#include "UI.h"
#include "Console.h"
#include "Album.h"
#include "ScreenManager.h"
#include "SubSongScreen.h"
#include "UserManager.h"
#include "Utils.h"
#include "SubListScreen.h"

#include <memory>

namespace sb
{
	class SubPlaylistScreen : public SubScreen
	{
	public:
		SubPlaylistScreen(std::shared_ptr<Playlist> album)
			: playlist_(std::move(album))
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
			const int baseY = 4;

			titleLb_ = addElement<Label>();
			titleLb_->setText("[ StreamBeat - Playlist >> " + playlist_->getName() + " ]");
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);

			playBt_ = addElement<Button>();
			playBt_->setText("Reproducir");
			playBt_->centerX(consoleSize.x());
			playBt_->setY(baseY + 5);

			listSongsBt_ = addElement<Button>();
			listSongsBt_->setText("Listar canciones");
			listSongsBt_->setOnEnter([this] {;
				ScreenManager::instance().pushSubScreen(
					std::make_unique<SubListScreen<Song>>("[ " + playlist_->getName() + " >> Songs ]", playlist_->getSongs(), [] (std::shared_ptr<Song> target) {
						ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
						}));
				});
			listSongsBt_->centerX(consoleSize.x());
			listSongsBt_->setY(baseY + 10);

			deletePlalist_ = addElement<Button>();
			deletePlalist_->setText("Eliminar Playlist");
			deletePlalist_->centerX(consoleSize.x());
			deletePlalist_->setY(baseY + 15);
			deletePlalist_->setOnEnter([this] {
				UserManager::instance().getCurrentLibrary().deletePlaylist(playlist_->getName());
				ScreenManager::instance().navigateToRoot(ScreenNames::Library);
				});

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
		std::shared_ptr<Playlist> playlist_;
		Button* playBt_{ nullptr };
		Button* listSongsBt_{ nullptr };
		Button* deletePlalist_{ nullptr };
		Button* backBt_{ nullptr };
	};
}