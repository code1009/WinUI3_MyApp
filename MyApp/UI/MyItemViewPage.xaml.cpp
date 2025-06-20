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

        ItemCountTextBlock_Update();
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
        InfoBarSeverity inforBarSeverity = InfoBarSeverity::Success;
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t itemCount = selectedItems.Size();
        if (itemCount > 0)
        {
            selectedItems.Clear();
     
            inforBarMessage = std::to_wstring(itemCount) + L"개의 항목을 선택 해제 했습니다.";
        }
        else
        {
            inforBarMessage = L"선택 항목이 없습니다.";
            inforBarSeverity = InfoBarSeverity::Warning;
		}


        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::AddButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity = InfoBarSeverity::Success;
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        auto selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 1)
        {
			inforBarMessage = L"선택 항목이 여러개입니다.\n뒤에 추가 될 한 개의 항목을 선택 하십시오.";
			inforBarSeverity = InfoBarSeverity::Warning;
        }
        else if (selectedItemCount == 1)
        {
			auto item = selectedItems.GetAt(0).as<winrt::MyApp::MyItem>();
            uint32_t itemPosition = 0;
            auto items = Items();
            auto found = items.IndexOf(item, itemPosition);
            if (found)
            {
                inforBarMessage = std::to_wstring(itemPosition + 1) + L"번째 항목 뒤에 추가합니다.";
            }
            else
            {
                inforBarMessage = L"항목을 찾을 수 없습니다.";
                inforBarSeverity = InfoBarSeverity::Error;
            }
        }
        else if (selectedItemCount == 0)
        {
            inforBarMessage = L"맨 막지막 위치에 추가합니다.";
        }


        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::EditButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity = InfoBarSeverity::Success;
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        auto selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 1)
        {
            inforBarMessage = L"선택 항목이 여러개입니다.\n한 개의 항목을 선택 하십시오.";
            inforBarSeverity = InfoBarSeverity::Warning;
        }
        else if (selectedItemCount == 1)
        {
            auto item = selectedItems.GetAt(0).as<winrt::MyApp::MyItem>();
            uint32_t itemPosition = 0;
            auto items = Items();
            auto found = items.IndexOf(item, itemPosition);
            if (found)
            {
                inforBarMessage = std::to_wstring(itemPosition + 1) + L"번째 항목을 편집합니다.";
            }
            else
            {
                inforBarMessage = L"항목을 찾을 수 없습니다.";
                inforBarSeverity = InfoBarSeverity::Error;
            }
        }
        else if (selectedItemCount == 0)
        {
            inforBarMessage = L"선택 항목이 없습니다.\n한 개의 항목을 선택 하십시오.";
            inforBarSeverity = InfoBarSeverity::Warning;
        }


        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::DeleteButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity = InfoBarSeverity::Success;
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t count = selectedItems.Size();
        if (count == 0)
        {
            inforBarMessage = L"선택 항목이 없습니다..\n한 개 이상의 항목을 선택 하십시오.";
            inforBarSeverity = InfoBarSeverity::Warning;
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
            return;
        }


        std::vector<winrt::MyApp::MyItem> itemsToRemove;
        for (auto const& item : selectedItems)
        {
            itemsToRemove.push_back(item.as<winrt::MyApp::MyItem>());
        }


        for (auto const& item : itemsToRemove)
        {
            uint32_t itemPosition = 0;
			auto found = Items().IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarMessage = L"항목을 찾을 수 없습니다. : " + item.Title();
                inforBarSeverity = InfoBarSeverity::Error;
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
                continue;
			}
            Items().RemoveAt(itemPosition);
        }


        ItemGridView().SelectedItems().Clear();
        ItemCountTextBlock_Update();


        inforBarMessage = std::to_wstring(count) + L"개 항목을 삭제했습니다.";
        inforBarSeverity = InfoBarSeverity::Success;
        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::DeleteAllButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity = InfoBarSeverity::Success;
        std::wstring inforBarMessage;


        auto items = Items();
        uint32_t count = items.Size();
        if (count == 0)
        {
			inforBarMessage = L"삭제할 항목이 없습니다.";
            inforBarSeverity = InfoBarSeverity::Warning;
        }
        else
        {
            items.Clear();
            ItemGridView().SelectedItems().Clear();
            ItemCountTextBlock_Update();

            inforBarMessage = L"모든 항목을 삭제했습니다.(" + std::to_wstring(count) + L"개)";
        }
        

        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::FindButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity = InfoBarSeverity::Success;
        std::wstring inforBarMessage;


		inforBarMessage = L"검색 기능은 아직 구현되지 않았습니다.";


        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::ItemCountTextBlock_Update(void)
    {
		//std::size_t itemCount = MyViewModel::Instance().Items().Size();
        std::size_t itemCount = Items().Size();

        ItemCountTextBlock().Text(
            (L"항목: " + std::to_wstring(itemCount) + L" 개").c_str()
        );
    }
}

