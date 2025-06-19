#include "pch.h"

#include "SettingsPage.xaml.h"

#if __has_include("SettingsPage.g.cpp")

#include "SettingsPage.g.cpp"

#endif

#include "Configuration.h"

namespace winrt
{
    using namespace Microsoft::UI::Xaml;
    using namespace Microsoft::UI::Xaml::Controls;
    using namespace Microsoft::UI::Xaml::Navigation;
    using namespace Windows::Foundation;
}

namespace winrt::MyApp::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
    }

    void SettingsPage::OnNavigatedTo(NavigationEventArgs const& eventArgs)
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


        for (UIElement&& c : themePanel().Children())
        {
            auto tag = c.as<RadioButton>().Tag().as<ElementTheme>();
            if (tag == Config::CurrentTheme)
            {
                auto radioButton = c.as<RadioButton>();
                radioButton.IsChecked(true);
            }
        }
    }

    void SettingsPage::OnThemeRadioButtonChecked(IInspectable const& sender, RoutedEventArgs const& /*eventArgs*/)
    {
        auto radioButton = sender.as<RadioButton>();
        auto selectedTheme = unbox_value<ElementTheme>(radioButton.Tag());


        if (_MainPage)
        {
            auto content = _MainPage.Content().as<Grid>();

            if (content != nullptr)
            {
                content.RequestedTheme(selectedTheme);
                Config::CurrentTheme = content.RequestedTheme();
            }
        }
    }
}
