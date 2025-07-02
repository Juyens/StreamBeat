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
			bool focused = false, const Palette& focusPalette = PalettePresets::Focus);

		void setBorderPalette(const Palette& palette);
		const Palette& getBorderPalette() const;

		void setBorderForeground(WORD foreground);
		void setBorderBackground(WORD background);

		void setFocusPalette(const Palette& palette);
		const Palette& getFocusPalette() const;

		void setFocusForeground(WORD foreground);
		void setFocusBackground(WORD background);

		void setOnEnter(std::function<void()> callback);

		void setFocus(bool isFocus);
		bool hasFocus() const;

		void setMonopolizeFocus(bool enable);
		bool wantsExclusiveInput() const;

		void focus();
		void blur();

		void render() override = 0;
		virtual void handleInput(const InputEvent& event) = 0;

	protected:
		virtual void onFocus() {}
		virtual void onBlur() {}

	protected:
		Palette borderPalette_{ PalettePresets::Default };
		Palette focusPalette_{ PalettePresets::Focus };
		bool hasFocus_{ false };
		bool monopolizeFocus_{ false };
		std::function<void()> onEnter_;
	};
}