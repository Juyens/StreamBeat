#pragma once

namespace sb::utils
{
    inline int centeredX(int totalWidth, int contentWidth) 
    {
        if (contentWidth > totalWidth) 
            return 0;

        return (totalWidth - contentWidth) / 2;
    }

    struct PositionedPair 
    {
        int leftX;
        int rightX;
        int y;
    };

    PositionedPair getCenteredPairX(int totalWidth, int fieldWidth, int spacing, int y) 
    {
        const int totalFieldsWidth = fieldWidth * 2 + spacing;
        const int startX = utils::centeredX(totalWidth, totalFieldsWidth);
        return { startX, startX + fieldWidth + spacing, y };
    }
}