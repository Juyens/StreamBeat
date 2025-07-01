#pragma once

#include "WindowHeader.h"

#include <sstream>
#include <stdexcept>

#define WINAPI_REQUIRE_HANDLE(h) sb::internal::checkHandle(h, __FUNCTION__)
#define WINAPI_REQUIRE_HWND(h) sb::internal::checkHwnd(h, __FUNCTION__)
#define WINAPI_REQUIRE_SUCCESS(res) sb::internal::requireWinApiSuccess(res, __FUNCTION__)

namespace sb::internal
{
	inline void throwLastError(const char* context)
	{
		DWORD errorCode = GetLastError();

		LPSTR errorBuffer = nullptr;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			errorCode,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			(LPSTR)&errorBuffer,
			0,
			nullptr
		);

		std::ostringstream oss;
		oss << "WinAPI call failed ";

		if (context)
			oss << " [" << context << "]";

		oss << " with error code " << errorCode << " >> " << errorBuffer;

		if (errorBuffer)
			LocalFree(errorBuffer);

		throw std::runtime_error(oss.str());
	}

	inline void checkHwnd(HWND hwnd, const char* context)
	{
		if (hwnd != nullptr)
			return;

		throwLastError(context);
	}

	inline void checkHandle(HANDLE handle, const char* context)
	{
		if (handle && handle != INVALID_HANDLE_VALUE)
			return;

		throwLastError(context);
	}

	inline void requireWinApiSuccess(BOOL result, const char* context)
	{
		if (result)
			return;

		throwLastError(context);
	}
}