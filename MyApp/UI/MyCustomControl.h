#pragma once

#include "MyCustomControl.g.h"

namespace winrt::MyApp::implementation
{
    struct MyCustomControl : MyCustomControlT<MyCustomControl>
    {
    private:
        winrt::Windows::UI::Color _BackgroundColor{ winrt::Windows::UI::Colors::Blue() };

    public:
        MyCustomControl();

        void Control_Loaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void Control_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);

    public:
        winrt::Windows::UI::Color BackgroundColor();
        void BackgroundColor(winrt::Windows::UI::Color const& value);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MyCustomControl : MyCustomControlT<MyCustomControl, implementation::MyCustomControl>
    {
    };
}
