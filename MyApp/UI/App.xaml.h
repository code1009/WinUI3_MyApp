#pragma once

#include "App.xaml.g.h"

namespace winrt::MyApp::implementation
{
    struct App : AppT<App>
    {
    public:
        App();

    public:
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const& eventArgs);

    private:
        winrt::Microsoft::UI::Xaml::Window _Window{ nullptr };
    };
}
