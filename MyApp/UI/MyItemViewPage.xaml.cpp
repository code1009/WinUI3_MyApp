#include "pch.h"

#include "MyItem.h"

#include "MyItemViewPage.xaml.h"

#if __has_include("MyItemViewPage.g.cpp")

#include "MyItemViewPage.g.cpp"

#endif

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

        _MyItems = winrt::single_threaded_observable_vector<MyApp::MyItem>();

        MyApp::MyItem item1;
        item1.Title(L"제목1");
        item1.Subtitle(L"부제목1");
        item1.Description(L"설명1");
        _MyItems.Append(item1);

        MyApp::MyItem item2;
        item2.Title(L"제목2");
        item2.Subtitle(L"부제목2");
        item2.Description(L"설명2");
        _MyItems.Append(item2);

        MyApp::MyItem item3;
        item3.Title(L"제목3");
        item3.Subtitle(L"부제목3");
        item3.Description(L"설명3");
        _MyItems.Append(item3);
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

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> MyItemViewPage::MyItems()
    {
        return _MyItems;
    }
}
