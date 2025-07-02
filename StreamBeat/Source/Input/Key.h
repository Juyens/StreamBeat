#pragma once

#include "WindowHeader.h"

#include <functional>
#include <optional>

namespace sb
{
	enum class Key : int
	{
		Escape = VK_ESCAPE,
		Enter = VK_RETURN,
		Space = VK_SPACE,
		Backspace = VK_BACK,
		Delete = VK_DELETE,

		Up = VK_UP,
		Down = VK_DOWN,
		Left = VK_LEFT,
		Right = VK_RIGHT,

		A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45,
		F = 0x46, G = 0x47, H = 0x48, I = 0x49, J = 0x4A,
		K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F,
		P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
		U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A
	};
}

namespace std
{
	template <>
	struct hash<sb::Key>
	{
		std::size_t operator()(const sb::Key& key) const noexcept
		{
			return std::hash<int>{}(static_cast<int>(key));
		}
	};
}