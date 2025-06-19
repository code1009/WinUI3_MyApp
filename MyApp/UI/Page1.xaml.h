#pragma once

#include "Page1.g.h"

namespace winrt::MyApp::implementation
{
    struct Page1 : Page1T<Page1>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };

    public:
        Page1();

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void SuccessMessage_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);
        void ErrorMessage_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);
        void InformationalMessage_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);
        void ClearMessage_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&);

    };
}

namespace winrt::MyApp::factory_implementation
{
    struct Page1 : Page1T<Page1, implementation::Page1>
    {
    };
}
