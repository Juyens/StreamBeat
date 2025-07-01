#pragma once

enum Style
{
	None = 0,
	TitleBar = 1 << 0,
	Resize = 1 << 1,
	Minimize = 1 << 2,
	Maximize = 1 << 3,
	Close = 1 << 4,
	Default = TitleBar | Resize | Minimize | Maximize | Close
};

inline Style operator|(Style s1, Style s2)
{
	return static_cast<Style>(static_cast<int>(s1) | static_cast<int>(s2));
}