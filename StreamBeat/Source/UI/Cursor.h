#pragma once

#include <chrono>

namespace sb
{
	class Cursor
	{
	public:
		Cursor();

		void reset();
		void moveLeft();
		void moveRight(int maxIndex);
		void insert();
		void eraseBefore();
		void eraseAfter(int maxIndex);

		void hide();
		void show();

		void updateBlink();
		bool isVisible() const;

		void setIndex(int index);
		int getIndex() const;

		void setScrollOffset(int offset);
		int getScrollOffset() const;

		void clampScroll(int visibleWidth);

		void activate();
		void deactivate();

	private:
		int index_ = 0;
		int scrollOffset_ = 0;

		bool active_{ true };
		bool visible_{ true };
		std::chrono::steady_clock::time_point lastBlink_ = std::chrono::steady_clock::now();

		static constexpr std::chrono::milliseconds blinkInterval_{ 450 };
	};
}