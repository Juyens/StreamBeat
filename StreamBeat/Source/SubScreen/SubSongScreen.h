#pragma once

#include "SubScreen.h"
#include "UI.h"
#include "Console.h"
#include "Song.h"
#include "ScreenManager.h"

#include <memory>

namespace sb
{
	class SubSongScreen : public SubScreen
	{
	public:
		SubSongScreen(std::shared_ptr<Song> song)
			: song_(std::move(song))
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
			titleLb_->setText("[ StreamBeat - Song >> " + song_->getName() + " ]");
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);

			playBt_ = addElement<Button>();
			playBt_->setText("Reproducir");
			playBt_->centerX(consoleSize.x());
			playBt_->setY(baseY + 5);

			addLibraryBt_ = addElement<Button>();
			addLibraryBt_->setText("Agregar a la Biblioteca");
			addLibraryBt_->centerX(consoleSize.x());
			addLibraryBt_->setY(baseY + 10);

			viewInfoBt_ = addElement<Button>();
			viewInfoBt_->setText("Mostrar Informacion");
			viewInfoBt_->centerX(consoleSize.x());
			viewInfoBt_->setY(baseY + 15);

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
		std::shared_ptr<Song> song_;
		Button* playBt_{ nullptr };
		Button* addLibraryBt_{ nullptr };
		Button* viewInfoBt_{ nullptr };
		Button* backBt_{ nullptr };
	};
}