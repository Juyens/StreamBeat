#pragma once

#include "SubScreen.h"
#include "DataManager.h"
#include "UI.h"
#include "Console.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "TableView.h"
#include "SubArtistScreen.h"
#include "SubAlbumScreen.h"
#include "SubSongScreen.h"

namespace sb
{
	template<class T>
	class SubSearchScreen : public SubScreen
	{
	public:
		SubSearchScreen(const std::string& title)
			: title_(title)
		{
			onCreate();
			initializeFocus();
		}

		void update() override
		{
			if (DataManager::instance().isLoadCompleted())
			{
				if (prevSearch != searchBox_->getText())
				{
					auto items = DataManager::instance().findByNameContains<T>(searchBox_->getText());

					if (!items.empty())
					{
						tablaView_->setItems(items);
					}
					else
					{
						tablaView_->clear();
					}

					prevSearch = searchBox_->getText();
				}
			}
		}

	protected:
		void onCreate() override
		{
			const auto consoleSize = Console::getViewportSize();
			const int baseY = 3;

			titleLb_ = addElement<Label>();
			titleLb_->setText("[ StreamBeat - Search - " + title_ + " ]");
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);
			
			searchBox_ = addElement<TextBox>();
			searchBox_->setSize({ 45, 3 });
			searchBox_->centerX(consoleSize.x());
			searchBox_->setY(baseY);

			tablaView_ = addElement<TableView<T>>();
			tablaView_->setGridSize({ 2, 25 });
			tablaView_->centerX(consoleSize.x());
			tablaView_->setY(baseY + 4);
			tablaView_->setItemAction([] (std::shared_ptr<T> target)
				{
					if constexpr (std::is_same_v<T, Artist>)
						ScreenManager::instance().pushSubScreen(std::make_unique<SubArtistScreen>(target));
					else if constexpr (std::is_same_v<T, Album>)
						ScreenManager::instance().pushSubScreen(std::make_unique<SubAlbumScreen>(target));
					else if constexpr (std::is_same_v<T, Song>)
						ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(target));
					else
						throw std::logic_error("Tipo no soportado");
				});

			previousPageBt_ = addElement<Button>();
			previousPageBt_->setText("Previous Page");
			previousPageBt_->setY(baseY + 32);
			previousPageBt_->setOnEnter([this] { tablaView_->previousPage(); });

			nextPageBt_ = addElement<Button>();
			nextPageBt_->setText("Next Page");
			nextPageBt_->setY(baseY + 32);
			nextPageBt_->setOnEnter([this] { tablaView_->nextPage(); });

			previousPageBt_->setX(utils::centered(consoleSize.x(), nextPageBt_->getWidth() + previousPageBt_->getWidth() + 5));
			nextPageBt_->setX(previousPageBt_->getX() + previousPageBt_->getWidth() + 5);
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
		std::string title_;
		std::string prevSearch;
		TextBox* searchBox_{ nullptr };
		TableView<T> *tablaView_{ nullptr };
		Button* nextPageBt_{ nullptr };
		Button* previousPageBt_{ nullptr };
	};
}