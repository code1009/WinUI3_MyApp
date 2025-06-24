#pragma once

#include "App.xaml.g.h"
#include "UI\MyCustomControl.h"

namespace winrt::MyApp::implementation
{
    struct App : AppT<App>
    {
    private:
        winrt::Microsoft::UI::Xaml::Window _Window{ nullptr };

    public:
        App();

    public:
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const& eventArgs);
    };
}
