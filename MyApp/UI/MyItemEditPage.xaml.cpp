#include "pch.h"

#include "MyItemEditPage.xaml.h"

#if __has_include("MyItemEditPage.g.cpp")

#include "MyItemEditPage.g.cpp"

#endif

#include "NavigationParam.h"

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

        OutputDebugStringW(L"MyItemEditPage");
    }

    MyItemEditPage::~MyItemEditPage()
    {
        OutputDebugStringW(L"~MyItemEditPage");
    }

    void MyItemEditPage::OnNavigatedTo(NavigationEventArgs const& eventArgs)
    {
        //auto item = eventArgs.Parameter().try_as<winrt::MyApp::MyItem>();

        auto param = eventArgs.Parameter().try_as<winrt::MyApp::NavigationParam>();
        
        if (param)
        {
            _MainPage = param.MainPage();

            auto item = param.Param0().try_as<winrt::MyApp::MyItem>();

            if (item)
            {
                _Item = item;

                TitleTextBox().Text(_Item.Title());
                SubtitleTextBox().Text(_Item.Subtitle());
                DescriptionTextBox().Text(_Item.Description());
            }
        }

        OutputDebugStringW(L"MyItemEditPage.OnNavigatedTo");
    }

    void MyItemEditPage::OkButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        _MainPage.NotifyUser(L"확인", InfoBarSeverity::Informational);

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

    void MyItemEditPage::CancelButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        _MainPage.NotifyUser(L"취소", InfoBarSeverity::Informational);

        if (Frame().CanGoBack())
        {
            Frame().GoBack();
        }
    }
}
