#include "pch.h"

#include "Page1.xaml.h"

#if __has_include("Page1.g.cpp")

#include "Page1.g.cpp"

#endif

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
        auto mainPage = eventArgs.Parameter().try_as<winrt::MyApp::MainPage>();
        if (mainPage)
        {
            _MainPage = mainPage;
        }
        else
        {
            throw hresult_error(E_FAIL, L"MainPage is not available.");
        }
    }

    void Page1::SuccessMessage_Click(IInspectable const&, RoutedEventArgs const&)
    {
        _MainPage.NotifyUser(L"Everything was ok!", InfoBarSeverity::Success);
    }

    void Page1::ErrorMessage_Click(IInspectable const&, RoutedEventArgs const&)
    {
        _MainPage.NotifyUser(L"Something went wrong.", InfoBarSeverity::Error);
    }

    void Page1::InformationalMessage_Click(IInspectable const&, RoutedEventArgs const&)
    {
        _MainPage.NotifyUser(L"This is the informational bar.", InfoBarSeverity::Informational);
    }

    void Page1::ClearMessage_Click(IInspectable const&, RoutedEventArgs const&)
    {
        _MainPage.NotifyUser(L"", InfoBarSeverity::Informational);
    }
}
