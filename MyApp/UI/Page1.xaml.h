#pragma once

#include "Page1.g.h"

namespace winrt::MyApp::implementation
{
    struct Page1 : Page1T<Page1>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };
        Microsoft::UI::Xaml::DispatcherTimer _DispatcherTimer{ nullptr };
        int _TickCount{ 0 };

    public:
        Page1();

        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void DispatcherTimer_OnTick(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::Foundation::IInspectable const&);

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& eventArgs);

    public:
        void SuccessMessage_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void ErrorMessage_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void InformationalMessage_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void ClearMessage_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);

        winrt::Windows::Foundation::IAsyncAction CustomDialog_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        winrt::Windows::Foundation::IAsyncAction ContentDialog_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        winrt::Windows::Foundation::IAsyncAction FileOpenPicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        winrt::Windows::Foundation::IAsyncAction FileSavePicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        winrt::Windows::Foundation::IAsyncAction FolderPicker_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct Page1 : Page1T<Page1, implementation::Page1>
    {
    };
}
