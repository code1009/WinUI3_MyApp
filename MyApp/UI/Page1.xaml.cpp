#include "pch.h"

#include "Page1.xaml.h"

#if __has_include("Page1.g.cpp")

#include "Page1.g.cpp"

#endif

#include "NavigationParam.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::Foundation;

namespace winrt::MyApp::implementation
{
    Page1::Page1()
    {
        InitializeComponent();
    }

    void Page1::OnNavigatedTo(NavigationEventArgs const& eventArgs)
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
    }

    void Page1::SuccessMessage_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        _MainPage.NotifyUser(L"Everything was ok!", InfoBarSeverity::Success);
    }

    void Page1::ErrorMessage_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        _MainPage.NotifyUser(L"Something went wrong.", InfoBarSeverity::Error);
    }

    void Page1::InformationalMessage_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        _MainPage.NotifyUser(L"This is the informational bar.", InfoBarSeverity::Informational);
    }

    void Page1::ClearMessage_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        _MainPage.NotifyUser(L"", InfoBarSeverity::Informational);
    }

    winrt::Windows::Foundation::IAsyncAction Page1::DialogButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        MyApp::MyDialog dialog;
        dialog.XamlRoot(_MainPage.XamlRoot());
        auto result = co_await dialog.ShowAsync();
        
        /*
        if (co_await dialog.ShowAsync() != ContentDialogResult::Primary) 
        {
            co_return;
        }
        */
		
        std::wstring message = L"Dialog result:\n";

        switch (result)
        {
        case ContentDialogResult::Primary:
			message += L"Primary 버튼이 눌렸습니다.\n입력 값 = ";
            message += dialog.Input();
            _MainPage.NotifyUser(message.c_str(), InfoBarSeverity::Success);
            co_return;

        case ContentDialogResult::Secondary:
            message += L"Secondary 버튼이 눌렸습니다.\n입력 값 = ";
            message += dialog.Input();
            _MainPage.NotifyUser(message.c_str(), InfoBarSeverity::Success);
            co_return;

        case ContentDialogResult::None:
            message += L"Close 버튼이 눌렸습니다.\n입력 값 = ";
            message += dialog.Input();
            _MainPage.NotifyUser(message.c_str(), InfoBarSeverity::Success);
            co_return;

        default:
            co_return;
        }

        /*
        •	C++/WinRT의 IAsyncAction 코루틴 함수는 반환값이 없는 비동기 작업을 나타냅니다.
        •	함수 내에서 co_return;을 명시적으로 호출하지 않아도, 함수가 끝나면 자동으로 코루틴이 종료됩니다.
        •	반환값이 필요한 경우(IAsyncOperation<T> 등)에는 co_return value;가 필요하지만, IAsyncAction은 필요 없습니다.
        */
    }
}
