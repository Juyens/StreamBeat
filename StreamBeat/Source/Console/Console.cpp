#include "Console.h"
#include "WinCheck.h"
#include "Style.h"

namespace sb
{
	void Console::moveCursor(int x, int y)
	{
		if (x < 0 || y < 0)
			return;

		COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
		WINAPI_REQUIRE_SUCCESS(SetConsoleCursorPosition(output_, coord));
	}

	void Console::applyDefaultLayout(int width, int height)
	{
		disableSelection();
		setCursorVisibility(false);
		resizeConsole(width, height);
		initializeBuffer();
		clearBuffer();
	}

	void Console::disableSelection()
	{
		DWORD mode = 0;
		WINAPI_REQUIRE_SUCCESS(GetConsoleMode(input_, &mode));

		mode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_MOUSE_INPUT);
		mode |= ENABLE_EXTENDED_FLAGS;

		WINAPI_REQUIRE_SUCCESS(SetConsoleMode(input_, mode));
	}

	void Console::setTitle(const std::wstring& title)
	{
		WINAPI_REQUIRE_SUCCESS(SetConsoleTitleW(title.c_str()));
	}

	void Console::setIcon(const std::wstring& iconPath)
	{
		HICON hIcon = static_cast<HICON>(LoadImageW(nullptr, iconPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED));

		if (hIcon)
		{
			SendMessage(window_, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			SendMessage(window_, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
	}

	void Console::setStyle(int styleFlags)
	{
		WINAPI_REQUIRE_HWND(window_);

		LONG_PTR style = GetWindowLongPtr(window_, GWL_STYLE);
		style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_CAPTION);

		if (styleFlags & TitleBar)  style |= WS_CAPTION;
		if (styleFlags & Resize)    style |= WS_SIZEBOX;
		if (styleFlags & Minimize)  style |= WS_MINIMIZEBOX;
		if (styleFlags & Maximize)  style |= WS_MAXIMIZEBOX;

		SetLastError(0);
		LONG_PTR prevStyle = SetWindowLongPtr(window_, GWL_STYLE, style);
		DWORD err = GetLastError();

		if (prevStyle == 0 && err != 0) {
			internal::throwLastError("SetWindowLongPtr (GWL_STYLE)");
		}

		WINAPI_REQUIRE_SUCCESS(ShowScrollBar(window_, SB_BOTH, FALSE));

		WINAPI_REQUIRE_SUCCESS(SetWindowPos(window_, nullptr, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED));

		HMENU hMenu = GetSystemMenu(window_, FALSE);
		if (hMenu)
		{
			auto setMenuItem = [&] (UINT cmd, bool enabled)
				{
					UINT flags = MF_BYCOMMAND | (enabled ? MF_ENABLED : MF_GRAYED);
					WINAPI_REQUIRE_SUCCESS(EnableMenuItem(hMenu, cmd, flags) != (UINT)-1);
				};

			setMenuItem(SC_MINIMIZE, styleFlags & Style::Minimize);
			setMenuItem(SC_MAXIMIZE, styleFlags & Style::Maximize);
			setMenuItem(SC_CLOSE, styleFlags & Style::Close);

			WINAPI_REQUIRE_SUCCESS(DrawMenuBar(window_));
		}
	}

	void Console::setCursorVisibility(bool visible)
	{
		WINAPI_REQUIRE_HANDLE(output_);

		CONSOLE_CURSOR_INFO cursorInfo = {};
		WINAPI_REQUIRE_SUCCESS(GetConsoleCursorInfo(output_, &cursorInfo));

		cursorInfo.bVisible = static_cast<int>(visible);
		WINAPI_REQUIRE_SUCCESS(SetConsoleCursorInfo(output_, &cursorInfo));
	}

	void Console::resizeWindow(int width, int height)
	{
		COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
		WINAPI_REQUIRE_SUCCESS(SetConsoleScreenBufferSize(output_, bufferSize));

		CONSOLE_FONT_INFO fontInfo;
		WINAPI_REQUIRE_SUCCESS(GetCurrentConsoleFont(output_, FALSE, &fontInfo));

		COORD charSize = GetConsoleFontSize(output_, fontInfo.nFont);

		if (charSize.X == 0 || charSize.Y == 0)
			sb::internal::throwLastError("GetConsoleFontSize");

		int charWidth = charSize.X;
		int charHeight = charSize.Y;

		int pixelWidth = width * charWidth;
		int pixelHeight = height * charHeight;

		RECT rect = { 0, 0, pixelWidth, pixelHeight };
		WINAPI_REQUIRE_SUCCESS(AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE));

		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		RECT current;
		WINAPI_REQUIRE_SUCCESS(GetWindowRect(window_, &current));
		int x = current.left;
		int y = current.top;

		WINAPI_REQUIRE_SUCCESS(MoveWindow(window_, x, y, windowWidth, windowHeight, TRUE));
	}

	void Console::resizeConsole(int width, int height)
	{
		if (width <= 0 || height <= 0)
			sb::internal::throwLastError("resizeConsole: invalid dimensions");

		SMALL_RECT minimal = { 0, 0, 1, 1 };
		WINAPI_REQUIRE_SUCCESS(SetConsoleWindowInfo(output_, TRUE, &minimal));

		COORD size = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
		WINAPI_REQUIRE_SUCCESS(SetConsoleScreenBufferSize(output_, size));

		SMALL_RECT windowRect = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
		WINAPI_REQUIRE_SUCCESS(SetConsoleWindowInfo(output_, TRUE, &windowRect));
	}

	void Console::writeAt(int x, int y, const std::string& text, WORD foreground, WORD background)
	{
		if (isOutOfView(x, y))
			return;

		const size_t length = text.length();

		if (isFramebufferActive())
		{
			for (size_t i = 0; i < length; ++i)
			{
				int posX = x + static_cast<int>(i);
				int posY = y;

				if (posX >= 0 && posX < m_FrameBufferSize.x() && posY >= 0 && posY < m_FrameBufferSize.y())
				{
					size_t index = posY * m_FrameBufferSize.x() + posX;
					m_FrameBuffer[index].Char.AsciiChar = text[i];
					m_FrameBuffer[index].Attributes = foreground | background;
				}
			}
			return;
		}

		std::vector<CHAR_INFO> buffer(length);
		for (size_t i = 0; i < length; ++i)
		{
			buffer[i].Char.AsciiChar = text[i];
			buffer[i].Attributes = foreground | (background << 4);
		}

		COORD bufferSize = { static_cast<SHORT>(length), 1 };
		COORD bufferCoord = { 0, 0 };
		SMALL_RECT writeRegion = { static_cast<SHORT>(x), static_cast<SHORT>(y),
									static_cast<SHORT>(x + length - 1), static_cast<SHORT>(y) };

		WINAPI_REQUIRE_SUCCESS(WriteConsoleOutputA(output_, buffer.data(), bufferSize, bufferCoord, &writeRegion));
	}

	std::optional<sb::InputEvent> Console::readInputEvent()
	{
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD available = 0;

		if (!GetNumberOfConsoleInputEvents(hInput, &available) || available == 0)
			return std::nullopt;

		std::vector<INPUT_RECORD> buffer(available);
		DWORD read = 0;

		if (!ReadConsoleInput(hInput, buffer.data(), available, &read))
			return std::nullopt;

		for (DWORD i = 0; i < read; ++i)
		{
			const auto& record = buffer[i];

			if (record.EventType != KEY_EVENT) continue;

			const auto& ev = record.Event.KeyEvent;
			if (!ev.bKeyDown) continue;

			char c = ev.uChar.AsciiChar;

			if (c >= 32 && c <= 126)
				return InputEvent{ c, std::nullopt };

			switch (ev.wVirtualKeyCode)
			{
			case VK_RETURN:    return InputEvent{ std::nullopt, Key::Enter };
			case VK_BACK:      return InputEvent{ std::nullopt, Key::Backspace };
			case VK_DELETE:    return InputEvent{ std::nullopt, Key::Delete };
			case VK_ESCAPE:    return InputEvent{ std::nullopt, Key::Escape };
			case VK_LEFT:      return InputEvent{ std::nullopt, Key::Left };
			case VK_RIGHT:     return InputEvent{ std::nullopt, Key::Right };
			case VK_UP:        return InputEvent{ std::nullopt, Key::Up };
			case VK_DOWN:      return InputEvent{ std::nullopt, Key::Down };
			case VK_TAB:	   return InputEvent{ std::nullopt, Key::Tab };
			case VK_F2:        return InputEvent{ std::nullopt, Key::F2 };
			}
		}

		return std::nullopt;
	}

	Vector2i Console::getViewportSize()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi = {};
		WINAPI_REQUIRE_SUCCESS(GetConsoleScreenBufferInfo(output_, &csbi));

		SMALL_RECT windowRect = csbi.srWindow;
		COORD size = {};
		size.X = windowRect.Right - windowRect.Left + 1;
		size.Y = windowRect.Bottom - windowRect.Top + 1;

		return {static_cast<int>(size.X), static_cast<int>(size.Y) };
	}

	void Console::initializeBuffer()
	{
		m_FrameBufferSize = getViewportSize();

		if (m_FrameBufferSize.x() <= 0 || m_FrameBufferSize.y() <= 0)
		{
			m_FrameBuffer.clear();
			return;
		}

		m_FrameBuffer.resize(static_cast<size_t>(m_FrameBufferSize.x()) * static_cast<size_t>(m_FrameBufferSize.y()));
	}

	void Console::clearBuffer(WORD foreground /*= Color::Foreground::White*/, WORD background /*= Color::Background::Black*/, char fillChar /*= ' '*/)
	{
		WORD attributes = foreground | (background << 4);

		for (auto& cell : m_FrameBuffer)
		{
			cell.Char.AsciiChar = fillChar;
			cell.Attributes = attributes;
		}
	}


	void Console::present(int ms /*= 16*/)
	{
		COORD bufferSize = {};
		bufferSize.X = static_cast<SHORT>(m_FrameBufferSize.x());
		bufferSize.Y = static_cast<SHORT>(m_FrameBufferSize.y());

		SMALL_RECT writeRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };

		COORD bufferCoord = { 0, 0 };

		WINAPI_REQUIRE_SUCCESS(WriteConsoleOutputA(output_, m_FrameBuffer.data(), bufferSize, bufferCoord, &writeRegion));

		Sleep(ms);
	}

	bool Console::isOutOfView(int x, int y)
	{
		const auto limits = getViewportSize();
		return x < 0 || y < 0 || x >= limits.x() || y >= limits.y();
	}

	bool Console::isFramebufferActive()
	{
		return !m_FrameBuffer.empty() && m_FrameBufferSize.x() > 0 && m_FrameBufferSize.y() > 0;
	}
}
