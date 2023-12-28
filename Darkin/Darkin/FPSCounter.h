// FPSCounter.h
#pragma once

#include <opencv2/opencv.hpp>
#include <chrono>

class FPSCounter {
public:
    FPSCounter();

    void countFrame();
    void putFPS(cv::Mat& image);

private:
    std::chrono::high_resolution_clock::time_point lastTime;
    int frameCount;
    double fps;
};
