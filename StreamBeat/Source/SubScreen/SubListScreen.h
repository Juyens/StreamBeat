#pragma once

#include "SubScreen.h"
#include "TableView.h"
#include "Console.h"

#include <memory>

namespace sb
{
	template<class T>
	class SubListScren : public SubScreen
	{
	public:
		using Action = std::function<void(std::shared_ptr<T>)>;

	private:
		Action itemAction_;
		std::string title_;
		TableView<T>* tableView_{ nullptr };
		Button* nextPageBt_{ nullptr };
		Button* previousPageBt_{ nullptr };

	public:
		SubListScren(const std::string title, List<std::shared_ptr<T>>& items, Action action)
			: title_(title), itemAction_(std::move(action))
		{
			tableView_ = addElement<TableView<T>>();
			tableView_->setGridSize({ 2, 25 });
			tableView_->setItems(items);
			tableView_->centerX(Console::getViewportSize().x());
			tableView_->setY(7);
			tableView_->setItemAction(itemAction_);

			onCreate();
			initializeFocus();
		}

	protected:
		void onCreate() override
		{
			const auto consoleSize = Console::getViewportSize();
			const int baseY = 3;

			titleLb_ = addElement<Label>();
			titleLb_->setText(title_);
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);

			previousPageBt_ = addElement<Button>();
			previousPageBt_->setText("Previous Page");
			previousPageBt_->setY(baseY + 32);
			previousPageBt_->setOnEnter([this] { tableView_->previousPage(); });

			nextPageBt_ = addElement<Button>();
			nextPageBt_->setText("Next Page");
			nextPageBt_->setY(baseY + 32);
			nextPageBt_->setOnEnter([this] { tableView_->nextPage(); });

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
	};
}