#pragma once

#include "Vector2.h"
#include "Palette.h"
#include "PalettePresets.h"

namespace sb
{
	class Widget
	{
	public:
		Widget();
		explicit Widget(const Vector2i& position, const Vector2i& size, const Palette& palette);

		virtual ~Widget() = default;

		void setPalette(const Palette& palette);
		const Palette& getPalette() const;

		void setForeground(WORD foreground);
		void setBackground(WORD background);

		virtual void setPosition(const Vector2i& pos);
		virtual Vector2i getPosition() const;

		virtual void setX(int x);
		virtual int getX();

		virtual void setY(int y);
		virtual int getY();

		virtual void setSize(int width, int height);
		virtual void setSize(const Vector2i& size);
		virtual Vector2i getSize() const;

		void show();
		void hide();
		bool isVisible() const;

		virtual void render() = 0;

		void centerX(int areaWidth);
		void centerY(int areaHeight);

	protected:
		Palette palette_{ PalettePresets::Default };
		Vector2i position_{ 0, 0 };
		Vector2i size_{ 0, 0 };
		bool visible_{ true };
	};
}