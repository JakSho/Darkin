#include <windows.h>
#include "WindowCapture.h"
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

void DisplayWindow(HWND hwnd) {
    HDC hdcWindow = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Variables to store the screen's refresh rate
    DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);

    // Create an OpenCV window named "Window Capture"
    cv::namedWindow("Window Capture", cv::WINDOW_NORMAL);

    // Define a BITMAPINFOHEADER structure
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height; // Negative height to ensure top-down image
    bi.biPlanes = 1;
    bi.biBitCount = 24; // 24-bit RGB
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    while (true) {
        // Query the screen's current refresh rate
        if (EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm)) {
            std::cout << "Screen Refresh Rate: " << dm.dmDisplayFrequency << " Hz" << std::endl;
        }
        else {
            std::cerr << "Failed to retrieve screen refresh rate." << std::endl;
        }

        // Create an OpenCV Mat object to store the captured content
        cv::Mat frame(height, width, CV_8UC3);

        // Capture the content of the window
        HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
        HBITMAP hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
        SelectObject(hdcMemDC, hbmScreen);
        BitBlt(hdcMemDC, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);
        GetDIBits(hdcWindow, hbmScreen, 0, height, frame.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

        // Display the captured content in real-time using OpenCV
        cv::imshow("Window Capture", frame);

        DeleteObject(hbmScreen);
        DeleteObject(hdcMemDC);
        ReleaseDC(hwnd, hdcWindow);

        // Adjust the waitKey time to control the frame rate
        int key = cv::waitKey(16); // Adjust for desired frame rate (e.g., 60 FPS)
        if (key == 27) { // Exit when the 'Esc' key is pressed
            break;
        }
    }

    cv::destroyWindow("Window Capture");
}

void WindowCapture() {
    const wchar_t* windowTitle = L"Window Title";

    HWND targetWindow = FindWindow(nullptr, windowTitle);
    if (targetWindow == nullptr) {
        std::wcerr << L"Window not found." << std::endl;
        return;
    }
    DisplayWindow(targetWindow);
}