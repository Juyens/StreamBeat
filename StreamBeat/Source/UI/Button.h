#pragma once

#include "Interactive.h"

#include <string>
#include <functional>

namespace sb
{
	class Button : public Interactive
	{
	public:
		Button();
		explicit Button(const Vector2i& position, std::string text);

		void setText(const std::string& text);
		void setBorderVisible(bool visible);

		void render() override;
		void handleInput(const InputEvent& ev) override;

		void reset() override;

	private:
		void updateSize();

	private:
		std::string text_{ "Button" };
		bool isBorderVisible_{ true };
	};
}