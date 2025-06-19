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
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void OnThemeRadioButtonChecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
