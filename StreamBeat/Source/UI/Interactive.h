#pragma once

#include "Widget.h"
#include "Key.h"
#include "Palette.h"
#include "PalettePresets.h"
#include "Console.h"

namespace sb
{
	class Interactive : public Widget
	{
	public:
		Interactive();
		Interactive(const Vector2i& position, const Vector2i& size,
			bool focused = false);

		void setFocusPalette(const Palette& palette);
		const Palette& getFocusPalette() const;

		void setFocusForeground(WORD foreground);
		void setFocusBackground(WORD background);

		void setInactivePalette(const Palette& palette);
		const Palette& getInactivePalette() const;

		void setInactiveForeground(WORD foreground);
		void setInactiveBackground(WORD background);

		void setOnEnter(std::function<void()> callback);

		void setFocus(bool isFocus);
		bool hasFocus() const;

		void setMonopolizeFocus(bool enable);
		bool wantsExclusiveInput() const;

		void focus();
		void blur();

		void render() override = 0;
		virtual void handleInput(const InputEvent& event) = 0;

		void activate();
		void deactivate();

		bool hasActive() const;

	protected:
		virtual void onFocus() {}
		virtual void onBlur() {}

	protected:
		Palette inactivePalette_{ PalettePresets::Inactive };
		Palette focusPalette_{ PalettePresets::Focus };
		bool active_{ true };
		bool hasFocus_{ false };
		bool monopolizeFocus_{ false };
		std::function<void()> onEnter_;
	};
}