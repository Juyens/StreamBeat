#pragma once

#include "Screen.h"
#include "DataManager.h"
#include "UI.h"
#include "Console.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "TableView.h"

namespace sb
{
	template<class T>
	class SubSearchScreen : public Screen
	{
	public:
		SubSearchScreen(const std::string& context)
			: Screen(ScreenNames::Temporary), context_(context)
		{
			onCreate();
			initializeFocus();
		}

		void update() override
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

	protected:
		void onCreate() override
		{
			const auto consoleSize = Console::getViewportSize();
			const int baseY = 3;

			titleLb_ = addElement<Label>();
			titleLb_->setText("[ StreamBeat - Search - " + context_ + " ]");
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
		std::string context_;
		std::string prevSearch;
		Label* titleLb_{ nullptr };
		TextBox* searchBox_{ nullptr };
		TableView<T> *tablaView_{ nullptr };
		Button* nextPageBt_{ nullptr };
		Button* previousPageBt_{ nullptr };
	};
}