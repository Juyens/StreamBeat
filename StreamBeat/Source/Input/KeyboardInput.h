#pragma once

#include "Key.h"

#include <unordered_map>
#include <chrono>
#include <optional>

namespace sb
{
	struct KeyRepeatState
	{
		bool wasPressed = false;
		std::chrono::steady_clock::time_point lastTriggerTime;
		bool initialDelayPassed = false;
	};

	class KeyboardInput
	{
	public:
		static void initialize(int initialDelayMs, int repeatIntervalMs);
		static bool isKeyPressed(Key key);
		static std::optional<Key> getPressedKey();

	private:
		inline static int initialDelay{ 400 };
		inline static int repeatInterval{ 80 };
		inline static std::unordered_map<Key, KeyRepeatState> keyStates;
	};
}
