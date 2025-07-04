#pragma once

#include "Interactive.h"
#include "Drawing.h"
#include "PalettePresets.h"
#include "HashTable.h"
#include "List.h"
#include "Vector2.h"
#include "Utils.h"

#include <string>
#include <functional>
#include <memory>

namespace sb
{
	constexpr int itemWidth_ = 50;

	template <typename T>
	class TableView : public Interactive
	{
	public:
		using Action = std::function<void(std::shared_ptr<T>)>;

		TableView(const Vector2i& position = { 0, 0 }, int columns = 2, int rows = 10)
			: Interactive(position, { columns * itemWidth_ + 2, rows + 2 }),
			gridSize_{ columns, rows }
		{
			setMonopolizeFocus(false);
		}

		void setItems(List<std::shared_ptr<T>>& items)
		{
			items_ = std::move(items);
			names_.clear();

			for (uint i = 0; i < items_.size(); ++i)
			{
				names_.push_back(items_[i]->getName());
			}

			selectedIndex_ = 0;
			pageIndex_ = 0;
		}

		void bindAction(const std::string& label, Action action)
		{
			actions_.insert(label, std::move(action));
		}

		void render() override
		{
			if (!isVisible())
				return;

			Palette activePalette = getBorderPalette();

			if (isSelecting_ && hasActive())
				activePalette = PalettePresets::Selected;
			else if (!hasActive())
				activePalette = getInactivePalette();
			else if (hasFocus())
				activePalette = PalettePresets::Focus;
			else
				activePalette = PalettePresets::Default;

			Drawing::drawBox(getX(), getY(), getWidth(), getHeight(), BoxStyles::SingleLineBox, activePalette);

			int start = pageIndex_ * getPageSize();
			int end = std::min(start + getPageSize(), static_cast<int>(names_.size()));

			for (int i = start; i < end; ++i)
			{
				int localIndex = i - start;
				int col = localIndex / gridSize_.y();
				int row = localIndex % gridSize_.y();

				Vector2i pos = { getX() + 1 + col * itemWidth_, getY() + 1 + row };
				bool selected = (i == getSelectedGlobalIndex());

				Palette palette = selected ? PalettePresets::Selected :
					hasActive() ? PalettePresets::Default : getInactivePalette();

				int offsetX = sb::utils::centered(itemWidth_, static_cast<int>(names_[i].size()));
				Drawing::drawText(pos.x() + offsetX, pos.y(), names_[i], palette);
			}
		}

		void handleInput(const InputEvent& ev) override
		{
			if (!hasFocus())
				return;

			if (ev.specialKey.has_value())
			{
				Key key = ev.specialKey.value();

				if (key == Key::Enter)
				{
					if (!isSelecting_)
					{
						isSelecting_ = true;
						setMonopolizeFocus(true);
					}
					else
					{
						int index = getSelectedGlobalIndex();
						if (index < names_.size() && index < items_.size())
						{
							const std::string& name = names_[index];
							auto* action = actions_.find(name);
							if (action)
								(*action)(items_[index]);
						}
					}
					return;
				}

				if (isSelecting_)
				{
					if (key == Key::Escape)
					{
						isSelecting_ = false;
						setMonopolizeFocus(false);
						return;
					}

					if (key == Key::Up || key == Key::Down || key == Key::Left || key == Key::Right)
					{
						int cols = gridSize_.x();
						int rows = gridSize_.y();
						int localIndex = selectedIndex_;
						int col = localIndex / rows;
						int row = localIndex % rows;

						switch (key)
						{
						case Key::Up: if (row > 0) --row; break;
						case Key::Down:
							if (row + 1 < rows && getSelectedGlobalIndex() + 1 < names_.size()) ++row;
							break;
						case Key::Left: if (col > 0) --col; break;
						case Key::Right:
							if (col + 1 < cols && getSelectedGlobalIndex() + rows < names_.size()) ++col;
							break;
						default: break;
						}

						selectedIndex_ = col * rows + row;
					}
				}
			}
		}

		void nextPage()
		{
			if (pageIndex_ + 1 < getTotalPages())
			{
				++pageIndex_;
				selectedIndex_ = 0;
			}
		}

		void previousPage()
		{
			if (pageIndex_ > 0)
			{
				--pageIndex_;
				selectedIndex_ = 0;
			}
		}

		std::shared_ptr<T> getSelectedItem() const
		{
			int index = pageIndex_ * getPageSize() + selectedIndex_;
			if (index >= 0 && index < items_.size())
				return items_[index];
			return nullptr;
		}

		void clear()
		{
			items_.clear();
			names_.clear();
			actions_.clear();
			pageIndex_ = 0;
			selectedIndex_ = 0;
			isSelecting_ = false;
		}

	private:
		int getPageSize() const
		{
			return gridSize_.x() * gridSize_.y();
		}

		int getTotalPages() const
		{
			int total = static_cast<int>(names_.size());
			return (total + getPageSize() - 1) / getPageSize();
		}

		int getSelectedGlobalIndex() const
		{
			return pageIndex_ * getPageSize() + selectedIndex_;
		}

		void onFocus() override {}
		void onBlur() override {}

	private:
		Vector2i gridSize_;
		int pageIndex_{ 0 };
		int selectedIndex_{ 0 };
		bool isSelecting_{ false };

		List<std::shared_ptr<T>> items_;
		List<std::string> names_;
		HashTable<std::string, Action> actions_;
	};
}