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

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);

    public:
        void CancelButton_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void OkButton_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MyItemEditPage : MyItemEditPageT<MyItemEditPage, implementation::MyItemEditPage>
    {
    };
}
