#include <windows.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include "FPSCounter.h"

// Function to find a window by its title
HWND FindWindowByTitle(const std::string& title) {
    return FindWindowA(NULL, title.c_str());
}

// Function to capture a specific window
cv::Mat captureWindowMat(HWND hWnd) {
    // Get the device context (DC) for the window
    HDC hWindowDC = GetDC(hWnd);

    // Get the client area of the window
    RECT rect;
    GetClientRect(hWnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Create a compatible DC and a new bitmap
    HDC hCaptureDC = CreateCompatibleDC(hWindowDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hWindowDC, width, height);

    // Select the new bitmap into the capture DC and capture the window
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCaptureDC, hBitmap);
    BitBlt(hCaptureDC, 0, 0, width, height, hWindowDC, 0, 0, SRCCOPY);

    // Create an OpenCV image from the captured bitmap
    cv::Mat screen(height, width, CV_8UC4);
    BITMAPINFOHEADER bi = { sizeof(bi), width, -height, 1, 32, BI_RGB };
    GetDIBits(hCaptureDC, hBitmap, 0, height, screen.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // Clean up
    SelectObject(hCaptureDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hCaptureDC);
    ReleaseDC(hWnd, hWindowDC);

    return screen;
}

int GetScreenRefreshRate() {
    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
    return devMode.dmDisplayFrequency;  // Returns the refresh rate
}

int CalculateFrameDuration(int refreshRate) {
    if (refreshRate <= 0) return 16;  // Default to ~60Hz if invalid rate
    return 1000 / refreshRate;       // Milliseconds per frame
}

void WindowCapture() {
    HWND hWnd = FindWindowByTitle("bin");
    if (!hWnd) {
        std::cerr << "Window not found!\n";
        return;
    }

    FPSCounter fpsCounter;

    while (true) {
        cv::Mat window = captureWindowMat(hWnd);
        if (window.empty()) {
            std::cerr << "Failed to capture window or window is minimized.\n";
            break;  // Exit if capture failed
        }

        fpsCounter.countFrame();  // Update FPS count
        fpsCounter.putFPS(window);  // Draw FPS on the image

        cv::imshow("Captured Window", window);

        // Break the loop if the user presses a key
        if (cv::waitKey(1) >= 0) break;
    }
}