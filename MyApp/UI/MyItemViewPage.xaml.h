#pragma once

#include "MyItem.h"
#include "MyItemViewPage.g.h"

namespace winrt::MyApp::implementation
{
    struct MyItemViewPage : MyItemViewPageT<MyItemViewPage>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };

    public:
        MyItemViewPage();
        virtual ~MyItemViewPage();

    public:
        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& eventArgs);

    public:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> Items();

    public:
        //void ItemGridView_ItemClick(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& eventArgs);
        //void ItemGridView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& eventArgs);

    public:
        void UnselectAllButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void EditButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void DeleteButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void DeleteAllButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void FindButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);

		void AddItem(uint32_t position);
        void EditItem(uint32_t position);

    public:
		void ItemCountTextBlock_Update(void);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MyItemViewPage : MyItemViewPageT<MyItemViewPage, implementation::MyItemViewPage>
    {
    };
}
