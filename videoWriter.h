#pragma once

#include "hwndToMat.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <thread>
#include <mutex>

class VideoWriter
{
public:
    VideoWriter(std::unique_ptr<HwndToMat> &&capDesktop);
    ~VideoWriter() = default;

public:
    bool Open();
    void Write(std::chrono::seconds seconds);

private:
    std::unique_ptr<HwndToMat> capDesktop;
    cv::VideoWriter writer;
    double fps = 20.0;
    std::mutex endRecordFlagMutex;
};