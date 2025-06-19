#pragma once

#include "MyItem.h"
#include "MyItemViewPage.g.h"

namespace winrt::MyApp::implementation
{
    struct MyItemViewPage : MyItemViewPageT<MyItemViewPage>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };

    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> _MyItems;

    public:
        MyItemViewPage();

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);

    public:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> MyItems();
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MyItemViewPage : MyItemViewPageT<MyItemViewPage, implementation::MyItemViewPage>
    {
    };
}
