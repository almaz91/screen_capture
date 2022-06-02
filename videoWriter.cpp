#include "videoWriter.h"

VideoWriter::VideoWriter(std::unique_ptr<HwndToMat>&& capDesktop) :
    capDesktop{std::move(capDesktop)}
{   
};

bool VideoWriter::Open()
{
    cv::Mat desktopImage = this->capDesktop->GetImage();
    
    std::string filename = "./" + std::to_string(desktopImage.cols) + "x" + std::to_string(desktopImage.rows) + ".yuv";
    int codec = cv::VideoWriter::fourcc('Y', 'V', '1', '2');

    return this->writer.open(filename, codec, this->fps, desktopImage.size(), true);
};

void VideoWriter::Write(std::chrono::seconds seconds)
{
    bool endRecordFlag = false;

    std::thread th([&]()
        {
            std::this_thread::sleep_for(seconds);

            std::unique_lock<std::mutex> lock(this->endRecordFlagMutex);
            endRecordFlag = true;
        });

    while (true)
    {
        cv::Mat yuvImg;

        this->capDesktop->Read();
        auto capDesktopImage = this->capDesktop->GetImage();

        cv::cvtColor(capDesktopImage, yuvImg, cv::COLOR_BGR2YUV);
        writer << yuvImg;
        cv::waitKey(1000 / this->fps);

        std::unique_lock<std::mutex> lock(this->endRecordFlagMutex);
        if (endRecordFlag == true)
            break;
    }

    th.join();
};
