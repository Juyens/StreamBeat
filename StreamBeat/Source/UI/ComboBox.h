#pragma once

#include "Interactive.h"
#include "List.h"
#include "BoxStyle.h"
#include "Drawing.h"
#include "Key.h"

#include <string>
#include <functional>

namespace sb
{
    template<class T>
    class ComboBox : public Interactive
    {
    public:
        ComboBox()
            : Interactive()
        {
            setSize({ 30, 3 });
        }

        explicit ComboBox(const Vector2i& position, const Vector2i& size)
            : Interactive(position, size) {}

        template<typename U>
        void addItem(U&& item)
        {
            items_.push_back(std::forward<U>(item));
        }

        void removeItemAt(uint index)
        {
            if (index >= items_.size())
                throw std::out_of_range("removeItemAt: invalid index");
            items_.remove(index);
            if (selectedIndex_ == static_cast<int>(index))
                selectedIndex_ = -1;
            else if (selectedIndex_ > static_cast<int>(index))
                --selectedIndex_;
        }

        void setSelectedIndex(int index)
        {
            if (index < -1 || index >= static_cast<int>(items_.size()))
                throw std::out_of_range("setSelectedIndex: invalid index");
            selectedIndex_ = index;
        }

        int getSelectedIndex() const { return selectedIndex_; }

        T* getSelectedItem()
        {
            if (selectedIndex_ < 0 || selectedIndex_ >= static_cast<int>(items_.size()))
                return nullptr;
            return &items_[static_cast<uint>(selectedIndex_)];
        }

        const T* getSelectedItem() const
        {
            if (selectedIndex_ < 0 || selectedIndex_ >= static_cast<int>(items_.size()))
                return nullptr;
            return &items_[static_cast<uint>(selectedIndex_)];
        }

        void clear()
        {
            items_.clear();
            selectedIndex_ = -1;
        }

        uint itemCount() const { return items_.size(); }

        void handleInput(const InputEvent& ev) override
        {
            if (!hasFocus()) return;

            if (ev.specialKey.has_value())
            {
                switch (*ev.specialKey)
                {
                case Key::Enter:
                    if (!isSelecting_)
                    {
                        isSelecting_ = true;
                        setMonopolizeFocus(true);

                        if (selectedIndex_ < 0 && items_.size() > 0)
                            selectedIndex_ = 0;
                    }
                    else
                    {
                        isSelecting_ = false;
                        setMonopolizeFocus(false);
                        if (onEnter_) onEnter_();
                    }
                    break;

                case Key::Down:
                    if (isSelecting_ && selectedIndex_ < static_cast<int>(items_.size()) - 1)
                        ++selectedIndex_;
                    break;

                case Key::Up:
                    if (isSelecting_ && selectedIndex_ > 0)
                        --selectedIndex_;
                    break;

                case Key::Escape:
                    onBlur();
                    break;

                default:
                    break;
                }
            }
        }

        void render() override
        {
            const Palette& activePalette = hasFocus() ? getFocusPalette() : getBorderPalette();

            Drawing::drawBox(position_.x(), position_.y(), size_.x(), size_.y(),
                BoxStyles::SingleLineBox, activePalette);

            const int textY = position_.y() + size_.y() / 2;
            const int maxTextWidth = size_.x() - 2;

            std::string text;
            if (selectedIndex_ >= 0 && selectedIndex_ < static_cast<int>(items_.size()))
            {
                text = toString_(items_[static_cast<uint>(selectedIndex_)]);
            }
            else
            {
                text = "Elija una opcion";
            }

            if (isSelecting_)
                text += " [In-Selection]";

            if (static_cast<int>(text.size()) > maxTextWidth)
                text = text.substr(0, maxTextWidth);

            const int contentWidth = size_.x() - 2;
            int textX = position_.x() + (contentWidth - static_cast<int>(text.size())) / 2 + 1;
            if (textX < position_.x() + 1)
                textX = position_.x() + 1;

            Drawing::drawText(textX, textY, text, activePalette);
        }

        void setItemToString(std::function<std::string(const T&)> fn)
        {
            toString_ = std::move(fn);
        }

    protected:
        void onBlur() override
        {
            isSelecting_ = false;
            setMonopolizeFocus(false);
        }

    private:
        List<T> items_{};
        int selectedIndex_{ -1 };
        bool isSelecting_{ false };

        std::function<std::string(const T&)> toString_ = [] (const T&) {
            return "<item>";
            };
    };
}