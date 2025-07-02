#include "Cursor.h"

namespace sb
{
	Cursor::Cursor()
	{
		reset();
	}

	void Cursor::reset()
	{
		index_ = 0;
		scrollOffset_ = 0;
		visible_ = true;
		lastBlink_ = std::chrono::steady_clock::now();
	}

	void Cursor::moveLeft()
	{
		if (index_ > 0) --index_;
	}

	void Cursor::moveRight(int maxIndex)
	{
		if (index_ < maxIndex) ++index_;
	}

	void Cursor::insert()
	{
		++index_;
	}

	void Cursor::eraseBefore()
	{
		if (index_ > 0) --index_;
	}

	void Cursor::eraseAfter(int maxIndex)
	{
		if (index_ >= maxIndex && index_ > 0)
			--index_;
	}

	void Cursor::hide()
	{
		visible_ = false;
	}

	void Cursor::show()
	{
		visible_ = true;
	}

	void Cursor::updateBlink()
	{
		auto now = std::chrono::steady_clock::now();
		if (now - lastBlink_ >= blinkInterval_)
		{
			visible_ = !visible_;
			lastBlink_ = now;
		}
	}

	bool Cursor::isVisible() const
	{
		return visible_;
	}

	void Cursor::setIndex(int index)
	{
		index_ = index;
	}

	int Cursor::getIndex() const
	{
		return index_;
	}

	void Cursor::setScrollOffset(int offset)
	{
		scrollOffset_ = offset;
	}

	int Cursor::getScrollOffset() const
	{
		return scrollOffset_;
	}

	void Cursor::clampScroll(int visibleWidth)
	{
		if (index_ < scrollOffset_)
			scrollOffset_ = index_;
		else if (index_ >= scrollOffset_ + visibleWidth)
			scrollOffset_ = index_ - visibleWidth + 1;
	}
}
