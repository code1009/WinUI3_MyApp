#pragma once

#include "MyItem.h"
#include "MyItemEditPage.g.h"

namespace winrt::MyApp::implementation
{
    struct MyItemEditPage : MyItemEditPageT<MyItemEditPage>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };
		winrt::MyApp::MyItem _Item{ nullptr };

    public:
        MyItemEditPage();
        virtual ~MyItemEditPage();

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& eventArgs);

    public:
        void CancelButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void OkButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MyItemEditPage : MyItemEditPageT<MyItemEditPage, implementation::MyItemEditPage>
    {
    };
}
