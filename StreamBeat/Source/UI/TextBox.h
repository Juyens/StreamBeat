#pragma once

#include "Interactive.h"
#include "Cursor.h"

#include <string>
#include <functional>

namespace sb
{
	class TextBox : public Interactive
	{
	public:
		TextBox();
		explicit TextBox(const Vector2i& position, const Vector2i& size = {30, 1});

		void setText(const std::string& text);
		const std::string& getText() const;

		void handleInput(const InputEvent& ev) override;
		void render() override;

		void reset() override;

	private:
		void onFocus() override;
		void onBlur() override;

	private:
		std::string text_;
		Cursor cursor_;
	};
}