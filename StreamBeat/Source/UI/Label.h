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
		void setBorderVisible(bool visible);
		void render() override;

	private:
		void updateSize();

	private:
		std::string text_{ "Label" };
		bool isBorderVisible_{ false };
	};
}