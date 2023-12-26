#include <windows.h>
#include <opencv2/opencv.hpp>
#include <string>

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
    BITMAPINFOHEADER bi = {sizeof(bi), width, -height, 1, 32, BI_RGB};
    GetDIBits(hCaptureDC, hBitmap, 0, height, screen.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    // Clean up
    SelectObject(hCaptureDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hCaptureDC);
    ReleaseDC(hWnd, hWindowDC);

    return screen;
}

int main() {
    HWND hWnd = FindWindowByTitle("lib");
    if (!hWnd) {
        std::cerr << "Window not found!\n";
        return -1;
    }

    while (true) {
        cv::Mat window = captureWindowMat(hWnd);
        cv::imshow("Captured Window", window);

        // Break the loop if the user presses a key
        if (cv::waitKey(300) >= 0) break;  // Wait for 1 second (1000 milliseconds) and check for key press
    }

    return 0;
}
