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
using namespace Microsoft::UI::Xaml::Input;
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
        auto param = eventArgs.Parameter().try_as<MyApp::NavigationParam>();
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

    Collections::IObservableVector<MyApp::MyItem> MyItemViewPage::Items()
    {
		return MyViewModel::Instance().Items();
    }

#if 0
    void MyItemViewPage::ItemGridView_ItemClick(IInspectable const& /*sender*/, ItemClickEventArgs const& eventArgs)
    {
        MyApp::MyItem persistedItem = eventArgs.ClickedItem().as<MyApp::MyItem>();

        MyApp::NavigationParam param;
        param.MainPage(_MainPage);
        param.Param0(persistedItem);

        Frame().Navigate(xaml_typename<MyApp::MyItemEditPage>(), param);
    }

    void MyItemViewPage::ItemGridView_SelectionChanged(IInspectable const& /*sender*/, SelectionChangedEventArgs const& /*eventArgs*/)
    {
        std::wstring message;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t selectedItemCount = selectedItems.Size();
        message = L"선택된 항목 " + std::to_wstring(selectedItemCount) + L"개\n";
		OutputDebugStringW(message.c_str());

        for (auto item : ItemGridView().SelectedItems())
        {
            MyApp::MyItem persistedItem = item.as<MyApp::MyItem>();

			message = L"\t항목=" + persistedItem.Title() + L"\n";
            OutputDebugStringW(message.c_str());
		}
    }
#endif

    void MyItemViewPage::InfoBarMessage(std::wstring const& /*title*/, std::wstring const& message, InfoBarSeverity severity)
    {
        _MainPage.NotifyUser(message.c_str(), severity);
    }

    void MyItemViewPage::ItemGridView_RightTapped(IInspectable const& sender, RightTappedRoutedEventArgs eventArgs)
    {
        std::wstring inforBarMessage;


        GridView gridView = sender.as<GridView>();

        Item_MenuFlyout().ShowAt(gridView, eventArgs.GetPosition(gridView));

		auto frameworkElement = eventArgs.OriginalSource().as<FrameworkElement>();
        if (frameworkElement)
        {
            auto container = gridView.ContainerFromItem(frameworkElement.DataContext());
            if (container)
            {
                auto index = gridView.IndexFromContainer(container);
                if (index != -1)
                {
                    auto items = Items();
                    auto found = items.GetAt(index);
                    if (!found)
                    {
                        inforBarMessage = std::format(L"항목을 찾을 수 없습니다.");
                        InfoBarMessage(L"RightTapped", inforBarMessage, InfoBarSeverity::Error);

                        _RightTappedItem = nullptr;
                    }
                    else
                    {
                        inforBarMessage = std::format(L"{}번째 항목에서 찾았습니다.", index + 1);
                        InfoBarMessage(L"RightTapped", inforBarMessage);

                        _RightTappedItem = found;
                    }
                }
            }
		}
    }

    void MyItemViewPage::Item_MenuFlyout_Open(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        std::wstring inforBarMessage;


        if (_RightTappedItem)
        {
            auto item = _RightTappedItem;
            auto items = Items();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarMessage = std::format(L"항목을 찾을 수 없습니다.");
                InfoBarMessage(L"메뉴-열기", inforBarMessage, InfoBarSeverity::Error);
            }
            else
            {
                inforBarMessage = std::format(L"{}번째 항목에서 찾았습니다.", itemPosition + 1);
                InfoBarMessage(L"메뉴-열기", inforBarMessage);
            }
        }
        else
        {
            inforBarMessage = std::format(L"대상 항목을 찾을 수 없습니다.");
            InfoBarMessage(L"메뉴-열기", inforBarMessage, InfoBarSeverity::Error);
        }
    }

    void MyItemViewPage::Item_MenuFlyout_Remove(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
    }

    void MyItemViewPage::Item_MenuFlyout_Edit(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
    }

    void MyItemViewPage::UnselectAllButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 0)
        {
            selectedItems.Clear();
     
            inforBarMessage = std::format(L"{}개의 항목을 선택 해제 했습니다.", selectedItemCount);
            InfoBarMessage(L"전체 선택 해제", inforBarMessage);
        }
        else
        {
            inforBarMessage = std::format(L"선택 항목이 없습니다.");
            InfoBarMessage(L"전체 선택 해제", inforBarMessage, InfoBarSeverity::Warning);
        }
    }

    void MyItemViewPage::AddButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        std::wstring inforBarMessage;


        auto items = Items();
        auto selectedItems = ItemGridView().SelectedItems();
        auto selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 1)
        {
            inforBarMessage = std::format(L"한 개의 항목을 선택 하십시오.");
            InfoBarMessage(L"추가", inforBarMessage, InfoBarSeverity::Warning);
        }
        else if (selectedItemCount == 1)
        {
			auto item = selectedItems.GetAt(0).as<MyApp::MyItem>();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarMessage = std::format(L"항목을 찾을 수 없습니다.");
                InfoBarMessage(L"추가", inforBarMessage, InfoBarSeverity::Error);
            }
            else
            {
                inforBarMessage = std::format(L"{}번째 항목에 추가 합니다.", itemPosition + 1);
                InfoBarMessage(L"추가", inforBarMessage);


                AddItem(itemPosition);
            }
        }
        else if (selectedItemCount == 0)
        {
            inforBarMessage = std::format(L"막지막 항목 위치에 추가합니다.");
            InfoBarMessage(L"추가", inforBarMessage);


            AddItem(Items().Size());
        }
    }

    void MyItemViewPage::EditButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        std::wstring inforBarMessage;


        auto items = Items();
        auto selectedItems = ItemGridView().SelectedItems();
        auto selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 1)
        {
            inforBarMessage = std::format(L"한 개의 항목을 선택 하십시오.");
            InfoBarMessage(L"편집", inforBarMessage, InfoBarSeverity::Warning);
        }
        else if (selectedItemCount == 1)
        {
            auto item = selectedItems.GetAt(0).as<MyApp::MyItem>();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarMessage = std::format(L"항목을 찾을 수 없습니다.");
                InfoBarMessage(L"편집", inforBarMessage, InfoBarSeverity::Error);
            }
            else
            {
                inforBarMessage = std::format(L"{}번째 항목을 편집합니다.", itemPosition + 1);
                InfoBarMessage(L"편집", inforBarMessage);


                EditItem(itemPosition);
            }
        }
        else if (selectedItemCount == 0)
        {
            inforBarMessage = std::format(L"선택 항목이 없습니다.");
            InfoBarMessage(L"편집", inforBarMessage, InfoBarSeverity::Warning);
        }
    }

    void MyItemViewPage::AddItem(uint32_t position)
    {
        MyApp::MyItem item;
        item.Title(L"제목");
        item.Subtitle(L"부제목");
        item.Description(L"설명");
        
        if (position > Items().Size())
        {
            Items().Append(item);
        }
        else
        {
            Items().InsertAt(position, item);
		}

        MyApp::NavigationParam param;
        param.MainPage(_MainPage);
        param.Command(L"취소 시 목록에서 삭제");
        param.Param0(item);
        Frame().Navigate(xaml_typename<MyApp::MyItemEditPage>(), param);
    }

    void MyItemViewPage::EditItem(uint32_t position)
    {
        std::wstring inforBarMessage;


        if (position >= Items().Size())
        {
            inforBarMessage = std::format(L"항목의 위치가 잘못되었습니다.");
            InfoBarMessage(L"편집", inforBarMessage, InfoBarSeverity::Error);
        }
        else
        {
            MyApp::MyItem item;
            item = Items().GetAt(position);
            
            MyApp::NavigationParam param;
            param.MainPage(_MainPage);
            param.Param0(item);
            Frame().Navigate(xaml_typename<MyApp::MyItemEditPage>(), param);
		}
    }

    void MyItemViewPage::DeleteButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t selectedItemCount = selectedItems.Size();
        if (selectedItemCount == 0)
        {
            inforBarMessage = std::format(L"항목을 선택 하십시오.");
            InfoBarMessage(L"삭제", inforBarMessage, InfoBarSeverity::Warning);
            return;
        }


        std::vector<MyApp::MyItem> itemsToRemove;
        for (auto const& item : selectedItems)
        {
            itemsToRemove.push_back(item.as<MyApp::MyItem>());
        }


		auto items = Items();
        for (auto const& item : itemsToRemove)
        {
            uint32_t itemPosition = 0;
			auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarMessage = std::format(L"항목을 찾을 수 없습니다. : {}", item.Title());
                InfoBarMessage(L"삭제", inforBarMessage, InfoBarSeverity::Error);
			}
            else
            {
                items.RemoveAt(itemPosition);
            }
        }


        ItemGridView().SelectedItems().Clear();
        ItemCountTextBlock_Update();
        

        inforBarMessage = std::format(L"{}개 항목을 삭제했습니다.", selectedItemCount);
        InfoBarMessage(L"삭제", inforBarMessage);
    }

    void MyItemViewPage::DeleteAllButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        std::wstring inforBarMessage;


        auto items = Items();
        uint32_t itemCount = items.Size();
        if (itemCount == 0)
        {
            inforBarMessage = std::format(L"대상 항목이 없습니다.");
            InfoBarMessage(L"전체 삭제", inforBarMessage, InfoBarSeverity::Warning);
        }
        else
        {
            items.Clear();
            ItemGridView().SelectedItems().Clear();
            ItemCountTextBlock_Update();

            inforBarMessage = std::format(L"{}개 항목을 삭제했습니다.", itemCount);
            InfoBarMessage(L"전체 삭제", inforBarMessage);
        }
    }

    double MyItemViewPage::ItemGridView_GetItemRowHeight(uint32_t index)
    {
        auto container = ItemGridView().ContainerFromIndex(index);
        if (auto fe = container.try_as<FrameworkElement>())
        {
            return fe.ActualHeight();
        }
        return 0.0;
    }

    void MyItemViewPage::FindButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
/*
        auto language = winrt::Windows::Globalization::ApplicationLanguages::Languages();;
        std::wstring message;
        message = language;
        message += L"\n";
//        OutputDebugStringW(message.c_str());
*/

        std::wstring inforBarMessage;

        
        std::wstring keyword = FindTextBox().Text().c_str();
        if (keyword.empty())
        {
            inforBarMessage = std::format(L"검색어가 비어 있습니다.");
            InfoBarMessage(L"검색", inforBarMessage, InfoBarSeverity::Warning);
            return;
        }


        auto items = Items();
        uint32_t itemCount = items.Size();
        if (itemCount == 0)
        {
            inforBarMessage = std::format(L"대상 항목이 없습니다.");
            InfoBarMessage(L"검색", inforBarMessage, InfoBarSeverity::Warning);
            return;
        }


        for (auto const& element: items)
        {
			MyApp::MyItem item = element.as<MyApp::MyItem>();
            if (item.Title() == keyword )
            {
                uint32_t itemPosition = 0;
                auto found = items.IndexOf(item, itemPosition);
                if (!found)
                {
                    inforBarMessage = std::format(L"항목을 찾을 수 없습니다. : {}", item.Title());
                    InfoBarMessage(L"검색", inforBarMessage, InfoBarSeverity::Error);
                }
                else
                {
                    inforBarMessage = std::format(L"{}번쨰 항목 위치에 해당 항목을 찾았습니다.",
						itemPosition + 1
                    );
                    InfoBarMessage(L"검색", inforBarMessage);


                    ItemGridView().ScrollIntoView(item);


                    //auto rowHeight = ItemGridView_GetItemRowHeight(itemPosition) + 4.0;
                    //ItemGridViewScrollViewer().ChangeView(nullptr, static_cast<double>(36.0 + (itemPosition) * rowHeight), nullptr);
                }
                return;
			}            
        }


        inforBarMessage = std::format(L"검색 항목을 찾을 수 없습니다.");
        InfoBarMessage(L"검색", inforBarMessage, InfoBarSeverity::Warning);
    }

    void MyItemViewPage::FindTextBox_KeyDown(IInspectable const& /*sender*/, KeyRoutedEventArgs const& eventArgs)
    {
        if (eventArgs.Key() == Windows::System::VirtualKey::Enter)
        {
            FindButton_Click(nullptr, nullptr);
        }
    }

    void MyItemViewPage::ItemCountTextBlock_Update(void)
    {
		//auto items = MyViewModel::Instance().Items();
        auto items = Items();
        std::size_t itemCount = items.Size();

		std::wstring message = std::format(L"항목: {} 개", itemCount);
        ItemCountTextBlock().Text(message.c_str());
    }
}

