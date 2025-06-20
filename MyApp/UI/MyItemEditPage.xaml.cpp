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

        OutputDebugStringW(L"MyItemEditPage\n");
    }

    MyItemEditPage::~MyItemEditPage()
    {
        OutputDebugStringW(L"~MyItemEditPage\n");
    }

    void MyItemEditPage::OnNavigatedTo(NavigationEventArgs const& eventArgs)
    {
        auto param = eventArgs.Parameter().try_as<winrt::MyApp::NavigationParam>();
        if (param)
        {
            _MainPage = param.MainPage();
        }
        if (!_MainPage)
        {
            throw hresult_error(E_FAIL, L"MainPage is not available.");
        }

		_Command = param.Command();

        auto item = param.Param0().try_as<winrt::MyApp::MyItem>();
        if (item)
        {
            _Item = item;
            TitleTextBox().Text(_Item.Title());
            SubtitleTextBox().Text(_Item.Subtitle());
            DescriptionTextBox().Text(_Item.Description());
        }


        OutputDebugStringW(L"MyItemEditPage.OnNavigatedTo\n");
    }

    void MyItemEditPage::OkButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        auto title = TitleTextBox().Text();
        auto subtitle = SubtitleTextBox().Text();
        auto description = DescriptionTextBox().Text();
		_Item.Title(title);
		_Item.Subtitle(subtitle);
		_Item.Description(description);


        _MainPage.NotifyUser(L"편집을 완료 했습니다.", InfoBarSeverity::Success);


       if (Frame().CanGoBack())
       {
           Frame().GoBack();
       }
    }

    void MyItemEditPage::CancelButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        if (_Command == L"취소 시 목록에서 삭제")
        {
			auto item = _Item;
			auto items = MyViewModel::Instance().Items();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (found)
            {
                items.RemoveAt(itemPosition);

                _MainPage.NotifyUser(L"추가를 취소 했습니다.", InfoBarSeverity::Informational);
            }
            else
            {
                _MainPage.NotifyUser(L"추가 취소를 하지 못했습니다.", InfoBarSeverity::Error);
            }
        }
        else
        {
            _MainPage.NotifyUser(L"편집을 취소 했습니다.", InfoBarSeverity::Informational);
        }


        if (Frame().CanGoBack())
        {
            Frame().GoBack();
        }
    }
}
