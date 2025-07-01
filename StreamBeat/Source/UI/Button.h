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
		explicit Button(const Vector2i& position, std::string label);

		void setLabel(const std::string& text);

		void render() override;
		void handleInput(const InputEvent& ev) override;

	private:
		void updateSize();

	private:
		std::string label_{ "Button" };
	};
}