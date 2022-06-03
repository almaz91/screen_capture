#pragma once

#include <Windows.h>
#include <opencv2/core/mat.hpp>

class HwndToMat
{
public:
    HwndToMat(HWND hwindow, float scale = 1);
    ~HwndToMat();
    cv::Mat Read();

private:
    cv::Mat image;
    HWND hwnd;
    HDC hwindowDC, hwindowCompatibleDC;
    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    BITMAPINFOHEADER  bi;
};