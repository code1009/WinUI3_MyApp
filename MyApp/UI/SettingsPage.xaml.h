#pragma once

#include "SettingsPage.g.h"

namespace winrt::MyApp::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
    private:
		winrt::MyApp::MainPage _MainPage{ nullptr };

    public:
        SettingsPage();

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& eventArgs);
        void OnThemeRadioButtonChecked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
