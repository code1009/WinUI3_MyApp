#pragma once

#include "Page2.g.h"

namespace winrt::MyApp::implementation
{
    struct Page2 : Page2T<Page2>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };

    public:
        Page2();

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& eventArgs);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct Page2 : Page2T<Page2, implementation::Page2>
    {
    };
}
