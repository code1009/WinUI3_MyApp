#pragma once

namespace winrt::MyApp
{
    struct Config
    {
    public:
        static hstring FeatureName;
        static Microsoft::UI::Xaml::ElementTheme CurrentTheme;
    };
}
