#include "KeyboardInput.h"
#include "WindowHeader.h"

namespace sb
{
	void KeyboardInput::initialize(int initialDelayMs, int repeatIntervalMs)
	{
		initialDelay = initialDelayMs;
		repeatInterval = repeatIntervalMs;
	}

	bool KeyboardInput::isKeyPressed(Key key)
	{
		auto& state = keyStates.try_emplace(key).first->second;

		SHORT keyState = GetAsyncKeyState(static_cast<int>(key));
		bool isPressed = (keyState & 0x8000) != 0;

		if (!state.wasPressed && !isPressed)
			return false;

		auto now = std::chrono::steady_clock::now();

		if (state.lastTriggerTime.time_since_epoch().count() == 0)
		{
			state.lastTriggerTime = now;
		}

		if (isPressed)
		{
			if (!state.wasPressed)
			{
				state.wasPressed = true;
				state.lastTriggerTime = now;
				state.initialDelayPassed = false;
				return true;
			}
			
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - state.lastTriggerTime).count();
				if (!state.initialDelayPassed)
				{
					if (elapsed >= initialDelay)
					{
						state.lastTriggerTime = now;
						state.initialDelayPassed = true;
						return true;
					}
				}
				else
				{
					if (elapsed >= repeatInterval)
					{
						state.lastTriggerTime = now;
						return true;
					}
				}
		}
		else
		{
			state.wasPressed = false;
			state.initialDelayPassed = false;
		}

		return false;
	}

	std::optional<Key> KeyboardInput::getPressedKey()
	{
		static constexpr Key keys[] = {
			Key::Esc, Key::Enter, Key::Space, Key::Backspace,
			Key::Up, Key::Down, Key::Left, Key::Right,
			Key::A, Key::B, Key::C, Key::D, Key::E, Key::F,
			Key::G, Key::H, Key::I, Key::J, Key::K, Key::L,
			Key::M, Key::N, Key::O, Key::P, Key::Q, Key::R,
			Key::S, Key::T, Key::U, Key::V, Key::W, Key::X,
			Key::Y, Key::Z
		};

		for (Key key : keys)
		{
			if (isKeyPressed(key))
				return key;
		}

		return std::nullopt;
	}
}
