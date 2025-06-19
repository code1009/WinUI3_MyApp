#include "pch.h"

#include "MyItemEditPage.xaml.h"

#if __has_include("MyItemEditPage.g.cpp")

#include "MyItemEditPage.g.cpp"

#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::Foundation;

namespace winrt::MyApp::implementation
{
    MyItemEditPage::MyItemEditPage()
    {
        InitializeComponent();
    }

    void MyItemEditPage::OnNavigatedTo(NavigationEventArgs const& eventArgs)
    {
		auto item = eventArgs.Parameter().try_as<winrt::MyApp::MyItem>();
        if (item)
        {
            _Item = item;

            TitleTextBox().Text(_Item.Title());
            SubtitleTextBox().Text(_Item.Subtitle());
            DescriptionTextBox().Text(_Item.Description());
        }
    }

    void MyItemEditPage::OkButton_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        auto title = TitleTextBox().Text();
        auto subtitle = SubtitleTextBox().Text();
        auto description = DescriptionTextBox().Text();
		_Item.Title(title);
		_Item.Subtitle(subtitle);
		_Item.Description(description);


       if (Frame().CanGoBack())
       {
           Frame().GoBack();
       }
    }

    void MyItemEditPage::CancelButton_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        if (Frame().CanGoBack())
        {
            Frame().GoBack();
        }
    }
}
