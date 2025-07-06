#pragma once

#include "SubScreen.h"
#include "UI.h"
#include "Console.h"
#include "Album.h"
#include "ScreenManager.h"
#include "SubSongScreen.h"

#include <memory>

namespace sb
{
	class SubAlbumScreen : public SubScreen
	{
	public:
		SubAlbumScreen(std::shared_ptr<Album> album)
			: album_(std::move(album))
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
			titleLb_->setText("[ StreamBeat - Album >> " + album_->getName() + " ]");
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);

			playBt_ = addElement<Button>();
			playBt_->setText("Reproducir");
			playBt_->centerX(consoleSize.x());
			playBt_->setY(baseY + 5);

			listSongsBt_ = addElement<Button>();
			listSongsBt_->setText("Listar canciones");
			listSongsBt_->centerX(consoleSize.x());
			listSongsBt_->setY(baseY + 10);
			listSongsBt_->setOnEnter([this] {
				auto songs = DataManager::instance().getSongsByAlbum(album_ ->getName());
				ScreenManager::instance().pushSubScreen(
					std::make_unique<SubListScren<Song>>("[ " + album_->getName() + " >> Songs ]", songs, [] (std::shared_ptr<Song> target) {
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
		std::shared_ptr<Album> album_;
		Button* playBt_{ nullptr };
		Button* listSongsBt_{ nullptr };
		Button* addLibraryBt_{ nullptr };
		Button* backBt_{ nullptr };
	};
}