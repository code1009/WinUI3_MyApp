#include "pch.h"

#include "MyItem.h"

#include "MyItemViewPage.xaml.h"

#if __has_include("MyItemViewPage.g.cpp")

#include "MyItemViewPage.g.cpp"

#endif

#include "MyViewModel.h"
#include "MyItemEditPage.xaml.h"
#include "NavigationParam.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::Foundation;

namespace winrt::MyApp::implementation
{
    MyItemViewPage::MyItemViewPage()
    {
        InitializeComponent();

        OutputDebugStringW(L"MyItemViewPage\n");
    }

    MyItemViewPage::~MyItemViewPage()
    {
        OutputDebugStringW(L"~MyItemViewPage\n");
    }

    void MyItemViewPage::OnNavigatedTo(NavigationEventArgs const& eventArgs)
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

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> MyItemViewPage::Items()
    {
		return MyViewModel::Instance().Items();
    }

    void MyItemViewPage::ItemGridView_ItemClick(IInspectable const& /*sender*/, ItemClickEventArgs const& eventArgs)
    {
        winrt::MyApp::MyItem persistedItem = eventArgs.ClickedItem().as<MyApp::MyItem>();

        auto param = winrt::make<winrt::MyApp::implementation::NavigationParam>();
        param.MainPage(_MainPage);
        param.Param0(persistedItem);

        Frame().Navigate(xaml_typename<winrt::MyApp::MyItemEditPage>(), param);
    }

    void MyItemViewPage::ItemGridView_SelectionChanged(IInspectable const& /*sender*/, SelectionChangedEventArgs const& /*eventArgs*/)
    {
		OutputDebugStringW((L"Selected Item = " + std::to_wstring(ItemGridView().SelectedItems().Size()) + L"\n").c_str());

        for (auto item : ItemGridView().SelectedItems())
        {
            winrt::MyApp::MyItem persistedItem = item.as<winrt::MyApp::MyItem>();
            OutputDebugStringW((L"Selected Item: " + persistedItem.Title() + L"\n").c_str());
		}
        OutputDebugStringW(L"\n");
    }

    void MyItemViewPage::UnselectAllButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {

    }

    void MyItemViewPage::AddButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {

    }

    void MyItemViewPage::EditButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {

    }

    void MyItemViewPage::DeleteButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {

    }
    void MyItemViewPage::DeleteAllButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {

    }
    void MyItemViewPage::FindButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {

    }
}
