#pragma once

#include "WindowHeader.h"
#include "Color.h"
#include "Key.h"
#include "Vector2.h"

#include <string>
#include <vector>
#include <optional>

namespace sb
{
	struct InputEvent
	{
		std::optional<char> character;
		std::optional<sb::Key> specialKey;
	};

	class Console
	{
	public:
		static void moveCursor(int x, int y);
		static void applyDefaultLayout(int width, int height);
		static void disableSelection();
		static void setTitle(const std::wstring& title);
		static void setIcon(const std::wstring& iconPath);
		static void setStyle(int styleFlags);
		static void setCursorVisibility(bool visible);
		static void resizeWindow(int width, int height);
		static void resizeConsole(int width, int height);
		static void writeAt(int x, int y, const std::string& text, WORD foreground = Color::Foreground::White,
			WORD background = Color::Background::Black);

		static std::optional<InputEvent> readInputEvent();

		static Vector2i getViewportSize();
		static void initializeBuffer();

		static void clearBuffer(WORD foreground = Color::Foreground::White, 
			WORD background = Color::Background::Black, char fillChar = ' ');

		static void present(int ms = 16);
		static bool isOutOfView(int x, int y);

	private:
		inline static HWND window_{ GetConsoleWindow() };
		inline static HANDLE output_{ GetStdHandle(STD_OUTPUT_HANDLE) };
		inline static HANDLE input_{ GetStdHandle(STD_INPUT_HANDLE) };

		inline static std::vector<CHAR_INFO> m_FrameBuffer = {};
		inline static Vector2i m_FrameBufferSize = { 0, 0 };

		static bool isFramebufferActive();
	};
}