#pragma once

#include <string>

namespace sb
{
	struct BoxStyle
	{
		char topLeft;
		char topRight;
		char bottomLeft;
		char bottomRight;
		char horizontal;
		char vertical;
	};

	namespace BoxStyles
	{
        // Double-line pseudo graphic box (CP850 compatible)
        inline constexpr BoxStyle DoubleLineBox{
            static_cast<char>('\xC9'), // ╔
            static_cast<char>('\xBB'), // ╗
            static_cast<char>('\xC8'), // ╚
            static_cast<char>('\xBC'), // ╝
            static_cast<char>('\xCD'), // ═
            static_cast<char>('\xBA')  // ║
        };

        // Single-line pseudo graphic box (CP850 compatible)
        inline constexpr BoxStyle SingleLineBox{
            static_cast<char>('\xDA'), // ┌
            static_cast<char>('\xBF'), // ┐
            static_cast<char>('\xC0'), // └
            static_cast<char>('\xD9'), // ┘
            static_cast<char>('\xC4'), // ─
            static_cast<char>('\xB3')  // │
        };

        // Simplified ASCII-style box (fallback)
        inline constexpr BoxStyle SimpleLineBox{
            static_cast<char>('+'),    // +
            static_cast<char>('+'),    // +
            static_cast<char>('+'),    // +
            static_cast<char>('+'),    // +
            static_cast<char>('\xC4'), // ─
            static_cast<char>('\xB3')  // │
        };

        inline constexpr BoxStyle UnderscoreLineBox{
            static_cast<char>(' '),    
            static_cast<char>(' '),    
            static_cast<char>(' '),    
            static_cast<char>(' '),    
            static_cast<char>('\xC4'), // ─
            static_cast<char>(' ')   
        };
	}
}