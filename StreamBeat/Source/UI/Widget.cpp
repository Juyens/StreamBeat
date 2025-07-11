#include "Widget.h"

namespace sb
{
	Widget::Widget() = default;

	Widget::Widget(const Vector2i& position, const Vector2i& size)
		: position_(position), size_(size) {}

	void Widget::setPosition(const Vector2i& pos)
	{
		position_ = pos;
	}

	Vector2i Widget::getPosition() const
	{
		return position_;
	}

	void Widget::setX(int x)
	{
		position_.setX(x);
	}

	int Widget::getX()
	{
		return position_.x();
	}

	void Widget::setY(int y)
	{
		position_.setY(y);
	}

	int Widget::getY()
	{
		return position_.y();
	}

	void Widget::setWidth(int width)
	{
		size_.setX(width);
	}

	int Widget::getWidth() const
	{
		return size_.x();
	}

	void Widget::setHeight(int height)
	{
		size_.setY(height);
	}

	int Widget::getHeight() const
	{
		return size_.y();
	}

	void Widget::setSize(const Vector2i& size)
	{
		size_ = size;
	}

	Vector2i Widget::getSize() const
	{
		return size_;
	}

	void Widget::show()
	{
		visible_ = true;
	}

	void Widget::hide()
	{
		visible_ = false;
	}

	bool Widget::isVisible() const
	{
		return visible_;
	}

	void Widget::centerX(int areaWidth)
	{
		int x = (areaWidth - size_.x()) / 2;
		position_.setX(x);
	}

	void Widget::centerY(int areaHeight)
	{
		int y = (areaHeight - size_.y()) / 2;
		position_.setY(y);
	}
	
	void Widget::setTextPalette(const Palette& textPalette)
	{
		textPalette_ = textPalette;
	}

	const Palette& Widget::getTextPalette() const
	{
		return textPalette_;
	}

	void Widget::setTextForeground(WORD foreground)
	{
		textPalette_.foreground = foreground;
	}

	void Widget::setTextBackground(WORD background)
	{
		textPalette_.background = background;
	}

	void Widget::setBorderPalette(const Palette& palette)
	{
		borderPalette_ = palette;
	}

	const Palette& Widget::getBorderPalette() const
	{
		return borderPalette_;
	}

	void Widget::setBorderForeground(WORD foreground)
	{
		borderPalette_.foreground = foreground;
	}

	void Widget::setBorderBackground(WORD background)
	{
		borderPalette_.background = background;
	}
}