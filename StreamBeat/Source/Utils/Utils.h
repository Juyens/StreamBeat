#pragma once

namespace sb::utils
{
    inline int centeredX(int totalWidth, int contentWidth) 
    {
        if (contentWidth > totalWidth) 
            return 0;

        return (totalWidth - contentWidth) / 2;
    }
}