#pragma once

#include "MyItem.h"
#include "MyItemViewPage.g.h"

namespace winrt::MyApp::implementation
{
    struct MyItemViewPage : MyItemViewPageT<MyItemViewPage>
    {
    private:
        winrt::MyApp::MainPage _MainPage{ nullptr };
		winrt::MyApp::MyItem _RightTappedItem{ nullptr };

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

        void ItemGridView_RightTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs eventArgs);
        void Item_MenuFlyout_Edit(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void Item_MenuFlyout_Remove(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void Item_MenuFlyout_Open(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);

    public:
        void UnselectAllButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void EditButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void DeleteButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void DeleteAllButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);
        void FindButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& eventArgs);

        void FindTextBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& eventArgs);

		void AddItem(uint32_t position);
        void EditItem(uint32_t position);
        double ItemGridView_GetItemRowHeight(uint32_t index);

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
