#include "pch.h"

#include "MainPage.xaml.h"

#if __has_include("MainPage.g.cpp")

#include "MainPage.g.cpp"

#endif

#include "NavigationParam.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Animation;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;

namespace winrt::MyApp::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        
        _Scenarios = single_threaded_observable_vector<Scenario>(
            {
                Scenario{ L"페이지1", hstring(name_of<MyApp::Page1>())},
                Scenario{ L"페이지2", hstring(name_of<MyApp::Page2>())},
                Scenario{ L"데이터보기", hstring(name_of<MyApp::MyItemViewPage>())}
            }
        );
    }

    MainPage::~MainPage()
    {
    }

    Windows::Foundation::Collections::IVector<MyApp::Scenario> MainPage::Scenarios()
    {
		return _Scenarios;
    }

    void MainPage::NotifyUser(hstring const& strMessage, InfoBarSeverity const& severity)
    {
        // If called from the UI thread, then update immediately.
        // Otherwise, schedule a task on the UI thread to perform the update.
        if (this->DispatcherQueue().HasThreadAccess())
        {
            UpdateStatus(strMessage, severity);
        }
        else
        {
            DispatcherQueue().TryEnqueue(
                [strongThis = get_strong(), this, strMessage, severity]
                { 
                    UpdateStatus(strMessage, severity); 
                }
            );
        }
    }

    void MainPage::UpdateStatus(hstring const& strMessage, InfoBarSeverity severity)
    {
        InfoBar().Message(strMessage);
        InfoBar().IsOpen(!strMessage.empty());
        InfoBar().Severity(severity);
    }

    void MainPage::NavView_Loaded(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        for (auto&& s : Scenarios())
        {
            FontIcon fontIcon{};
            fontIcon.FontFamily(Microsoft::UI::Xaml::Media::FontFamily(L"Segoe MDL2 Assets"));
            fontIcon.Glyph(L"\uE82D");

            NavigationViewItem navViewItem{};
            navViewItem.Content(box_value(s.Title));
            navViewItem.Tag(box_value(s.ClassName));
            navViewItem.Icon(fontIcon);
            NavView().MenuItems().Append(navViewItem);
        }

        // NavView doesn't load any page by default, so load home page.
        NavView().SelectedItem(NavView().MenuItems().GetAt(0));

        // If navigation occurs on SelectionChanged, this isn't needed.
        // Because we use ItemInvoked to navigate, we need to call Navigate
        // here to load the home page.
        if (Scenarios().Size() > 0)
        {
            NavView_Navigate(Scenarios().GetAt(0).ClassName, nullptr);
        }
    }

    void MainPage::NavView_ItemInvoked(NavigationView const& /*sender*/, NavigationViewItemInvokedEventArgs const& eventArgs)
    {
        if (eventArgs.IsSettingsInvoked() == true)
        {
            hstring xamltypename = winrt::xaml_typename<SettingsPage>().Name;
            NavView_Navigate(xamltypename, eventArgs.RecommendedNavigationTransitionInfo());
        }
        else if (eventArgs.InvokedItemContainer() != nullptr)
        {
            auto navItemTag = winrt::unbox_value<hstring>(eventArgs.InvokedItemContainer().Tag());
            if (navItemTag != L"")
            {
                NavView_Navigate(navItemTag, eventArgs.RecommendedNavigationTransitionInfo());
            }
        }
    }

    void MainPage::NavView_Navigate(hstring navItemTag, NavigationTransitionInfo const& /*eventArgs*/)
    {
        TypeName pageType;

        if (navItemTag == winrt::xaml_typename<SettingsPage>().Name)
        {
            pageType = winrt::xaml_typename<SettingsPage>();
        }
        else
        {
            pageType.Name = navItemTag;
            pageType.Kind = TypeKind::Metadata;
        }

        // Get the page type before navigation so you can prevent duplicate
        // entries in the backstack.
        TypeName prePageType = ContentFrame().CurrentSourcePageType();

        // Only navigate if the selected page isn't currently loaded.
        if (prePageType.Name != pageType.Name)
        {
            MyApp::NavigationParam param;
            param.MainPage(*this);

            DrillInNavigationTransitionInfo drillIn;
            ContentFrame().Navigate(pageType, param, drillIn);
        }
    }

    void MainPage::NavView_BackRequested(NavigationView const& /*sender*/, NavigationViewBackRequestedEventArgs const& /*eventArgs*/)
    {
        if (ContentFrame().CanGoBack())
        {
            ContentFrame().GoBack();
        }
    }

    void MainPage::ContentFrame_Navigated(IInspectable const& /*sender*/, NavigationEventArgs const& eventArgs)
    {
        NavView().IsBackEnabled(ContentFrame().CanGoBack());

        if (ContentFrame().SourcePageType().Name == winrt::xaml_typename<SettingsPage>().Name)
        {
            // SettingsItem is not part of NavView.MenuItems, and doesn't have a Tag.
            NavView().SelectedItem((NavView().SettingsItem().as<NavigationViewItem>()));
            NavView().Header(winrt::box_value(L"Settings"));
        }
        else
        {
            for (auto&& item : NavView().MenuItems())
            {
                auto navViewItem = item.try_as<NavigationViewItem>();
                if (navViewItem != nullptr &&
                    winrt::unbox_value<hstring>(navViewItem.Tag()) == eventArgs.SourcePageType().Name)
                {
                    NavView().SelectedItem(navViewItem);
                    NavView().Header(navViewItem.Content());
                    break;
                }
            }
        }
    }
}
