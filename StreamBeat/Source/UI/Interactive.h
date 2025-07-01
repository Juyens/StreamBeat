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
		Interactive(const Vector2i& position, const Vector2i& size, const Palette& palette,
			bool focused = false, const Palette& focusPalette = PalettePresets::Focus);

		void setFocusPalette(const Palette& palette);
		const Palette& getFocusPalette() const;

		void setOnEnter(std::function<void()> callback);

		void setFocus(bool isFocus);
		bool hasFocus() const;

		void focus();
		void blur();

		void render() override = 0;
		virtual void handleInput(const InputEvent& event) = 0;

	protected:
		virtual void onFocus() {}
		virtual void onBlur() {}

	protected:
		Palette focusPalette_{ PalettePresets::Focus };
		bool hasFocus_{ false };

		std::function<void()> onEnter_;
	};
}