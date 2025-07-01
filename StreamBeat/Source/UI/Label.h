#pragma once

#include "Widget.h"
#include "Palette.h"
#include "Vector2.h"

#include <string>

namespace sb
{
	class Label : public Widget
	{
	public:
		Label();
		explicit Label(const Vector2i& position, const std::string& text);

		void setText(const std::string& text);
		const std::string& getText() const;

		void setTextPalette(const Palette& textPalette);
		const Palette& getTextPalette() const;

		void setTextForeground(WORD foreground);
		void setTextBackground(WORD background);

		void render() override;

	private:
		Palette textPalette_{ PalettePresets::Default };
		std::string text_{ "Label" };
	};
}