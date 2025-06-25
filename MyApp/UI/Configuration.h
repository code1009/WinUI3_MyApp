#pragma once

namespace winrt::MyApp
{
    struct Config
    {
    public:
        static hstring FeatureName;
        static HWND MainWindowHandle;
        static Microsoft::UI::Xaml::ElementTheme CurrentTheme;
    };
}
