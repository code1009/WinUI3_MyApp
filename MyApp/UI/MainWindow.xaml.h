#pragma once

#include "MainWindow.g.h"

namespace winrt::MyApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    private:
        HWND _hwnd{ nullptr };

    public:
        MainWindow();

    private:
        void SetWindowSize(HWND hwnd, const int width, const int height);
        HWND GetWindowHandle();
        void LoadIconFromFileSystem(HWND hwnd, wchar_t const* iconName);
        void ClipOrCenterRectToMonitorWin32(RECT& rc);
        void PlacementCenterWindowInMonitorWin32(HWND hwnd);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
