// FPSCounter.cpp
#include "FPSCounter.h"
#include <sstream>

FPSCounter::FPSCounter() : lastTime(std::chrono::high_resolution_clock::now()), frameCount(0), fps(0) {}

void FPSCounter::countFrame() {
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = currentTime - lastTime;

    // Update FPS every second
    if (elapsed.count() >= 1.0) {
        fps = frameCount / elapsed.count();
        lastTime = currentTime;
        frameCount = 0;
    }
}

void FPSCounter::putFPS(cv::Mat& image) {
    // Convert fps to a string with 2 decimal places
    std::ostringstream fpsTextStream;
    fpsTextStream.precision(2);
    fpsTextStream << std::fixed << fps;
    std::string fpsText = "FPS: " + fpsTextStream.str();

    // Draw the text on the image
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 2;
    cv::Point textOrg(10, 50); // Position the text at the top-left of the image
    cv::putText(image, fpsText, textOrg, fontFace, fontScale, cv::Scalar(0, 255, 0), thickness);
}
