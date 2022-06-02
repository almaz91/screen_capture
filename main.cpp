#pragma once

#include "hwndToMat.h"
#include "videoWriter.h"

#include <iostream>

int main()
{ 
    try
    {
        auto captureDesktop = std::make_unique<HwndToMat>(GetDesktopWindow());
        VideoWriter desktopWriter(std::move(captureDesktop));

        if (!desktopWriter.Open()) {
            std::cerr << "Could not open the output video file for write" << std::endl;
            return -1;
        }

        auto timeDuration = std::chrono::seconds(5);
        desktopWriter.Write(timeDuration);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception has been thrown: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}