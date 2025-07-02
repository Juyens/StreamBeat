#pragma once

namespace sb::utils
{
    inline int centered(int totalWidth, int contentWidth) 
    {
        if (contentWidth > totalWidth) 
            return 0;

        return (totalWidth - contentWidth) / 2;
    }
}