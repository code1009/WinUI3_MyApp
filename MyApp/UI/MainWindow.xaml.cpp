#include "pch.h"

#include "MainWindow.xaml.h"

#if __has_include("MainWindow.g.cpp")

#include "MainWindow.g.cpp"

#include "microsoft.ui.xaml.window.h" 
#include "Configuration.h"

#endif

#include "../Resource/Resource.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::MyApp::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        Title(L"MyApp");
        ExtendsContentIntoTitleBar(true);

        HWND hwnd = GetWindowHandle();
        LoadIconFromFileSystem(hwnd, L"Assets/windows-sdk.ico");
		
#if 0
#if 0
        HANDLE hSmallIcon = LoadImageW(nullptr, MAKEINTRESOURCEW(IDI_APP), IMAGE_ICON,
            GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
            0);
        HANDLE hBigIcon = LoadImageW(nullptr, MAKEINTRESOURCEW(IDI_APP), IMAGE_ICON,
            GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON),
            0);
		
        SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hSmallIcon));
        SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hBigIcon));
#else
        HICON hIcon = LoadIconW(nullptr, MAKEINTRESOURCEW(IDI_APP));
        if (hIcon)
        {
            SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
            SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
        }
#endif
#endif
        SetWindowSize(hwnd, 1920/2, 1080/2);
        PlacementCenterWindowInMonitorWin32(hwnd);

        Config::MainWindowHandle = hwnd;
    }

    HWND MainWindow::GetWindowHandle()
    {
        if (_hwnd == nullptr)
        {
            Window window = *this;
            window.as<IWindowNative>()->get_WindowHandle(&_hwnd);
        }
        return _hwnd;
    }

    void MainWindow::LoadIconFromFileSystem(HWND hwnd, wchar_t const* iconPath)
    {
        HANDLE hSmallIcon = LoadImageW(nullptr, iconPath, IMAGE_ICON,
            GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
            LR_LOADFROMFILE | LR_SHARED);
        SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hSmallIcon));

        HANDLE hBigIcon = LoadImageW(nullptr, iconPath, IMAGE_ICON,
            GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON),
            LR_LOADFROMFILE | LR_SHARED);
        SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hBigIcon));
    }

    void MainWindow::SetWindowSize(HWND hwnd, int width, int height)
    {
        // Win32 uses pixels and WinUI 3 uses effective pixels, so you should apply the DPI scale factor
        const UINT dpi = GetDpiForWindow(hwnd);
        const float scalingFactor = static_cast<float>(dpi) / 96;
        const int widthScaled = static_cast<int>(width * scalingFactor);
        const int heightScaled = static_cast<int>(height * scalingFactor);

        SetWindowPos(hwnd, nullptr, 0, 0, widthScaled, heightScaled, SWP_NOMOVE | SWP_NOZORDER);
    }

    void MainWindow::PlacementCenterWindowInMonitorWin32(HWND hwnd)
    {
        RECT windowMontiorRectToAdjust;
        GetWindowRect(hwnd, &windowMontiorRectToAdjust);
        ClipOrCenterRectToMonitorWin32(windowMontiorRectToAdjust);
        SetWindowPos(hwnd, nullptr, windowMontiorRectToAdjust.left,
            windowMontiorRectToAdjust.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void MainWindow::ClipOrCenterRectToMonitorWin32(RECT& adjustedWindowRect)
    {
        MONITORINFO mi{ sizeof(mi) };
        GetMonitorInfoW(MonitorFromRect(&adjustedWindowRect, MONITOR_DEFAULTTONEAREST), &mi);

        const auto& rcWork = mi.rcWork;
        const int w = adjustedWindowRect.right - adjustedWindowRect.left;
        const int h = adjustedWindowRect.bottom - adjustedWindowRect.top;

        adjustedWindowRect.left = rcWork.left + (rcWork.right - rcWork.left - w) / 2;
        adjustedWindowRect.top = rcWork.top + (rcWork.bottom - rcWork.top - h) / 2;
        adjustedWindowRect.right = adjustedWindowRect.left + w;
        adjustedWindowRect.bottom = adjustedWindowRect.top + h;
    }

    void MainWindow::Exit_MenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& /*eventArgs*/)
    {
        Close();
    }
}

