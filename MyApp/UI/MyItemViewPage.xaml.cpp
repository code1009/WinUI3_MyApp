#include "pch.h"

#include "MyItem.h"

#include "MyItemViewPage.xaml.h"

#if __has_include("MyItemViewPage.g.cpp")

#include "MyItemViewPage.g.cpp"

#endif

#include "MyViewModel.h"
#include "MyItemEditPage.xaml.h"

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

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> MyItemViewPage::Items()
    {
		return MyViewModel::Instance().Items();
    }

    void MyItemViewPage::ItemGridView_ItemClick(Windows::Foundation::IInspectable const, Microsoft::UI::Xaml::Controls::ItemClickEventArgs const e)
    {
        winrt::MyApp::MyItem persistedItem = e.ClickedItem().as<MyApp::MyItem>();

        Frame().Navigate(xaml_typename<winrt::MyApp::MyItemEditPage>(), e.ClickedItem()); // , m_suppress);
    }

    void MyItemViewPage::ItemGridView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
		//winrt::MyApp::MyItem persistedItem = e.OriginalSource().as<winrt::Microsoft::UI::Xaml::Controls::GridView>().SelectedItem().as < MyApp::MyItem
        
        for (auto x : ItemGridView().SelectedItems())
        {
            winrt::MyApp::MyItem persistedItem = x.as<winrt::MyApp::MyItem>();
            OutputDebugStringW((L"Selected Item: " + persistedItem.Title() + L"\n").c_str());
		}
        OutputDebugStringW(L"\n");
    }

}
