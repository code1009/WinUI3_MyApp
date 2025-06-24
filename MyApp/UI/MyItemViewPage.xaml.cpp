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
    void MyItemViewPage::ItemGridView_RightTapped(IInspectable const& sender, RightTappedRoutedEventArgs eventArgs)
    {
        InfoBarSeverity inforBarSeverity;
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
                        inforBarSeverity = InfoBarSeverity::Error;
                        inforBarMessage = std::format(L"[RightTapped] 항목을 찾을 수 없습니다.");
                        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);

                        _RightTappedItem = nullptr;
                    }
                    else
                    {
                        inforBarSeverity = InfoBarSeverity::Success;
                        inforBarMessage = std::format(L"[RightTapped] {}번째 항목에서 찾았습니다.", index + 1);
                        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);

                        _RightTappedItem = found;
                    }
                }
            }
		}
    }

    void MyItemViewPage::Item_MenuFlyout_Open(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        if (_RightTappedItem)
        {
            auto item = _RightTappedItem;
            auto items = Items();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarSeverity = InfoBarSeverity::Error;
                inforBarMessage = std::format(L"[MenuOpen] 항목을 찾을 수 없습니다.");
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
            }
            else
            {
                inforBarSeverity = InfoBarSeverity::Success;
                inforBarMessage = std::format(L"[MenuOpen] {}번째 항목에서 찾았습니다.", itemPosition + 1);
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
            }
        }
        else
        {
            inforBarSeverity = InfoBarSeverity::Error;
            inforBarMessage = std::format(L"[MenuOpen] 대상 항목을 찾을 수 없습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
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
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 0)
        {
            selectedItems.Clear();
     
            inforBarSeverity = InfoBarSeverity::Success;
            inforBarMessage = std::format(L"[Button] {}개의 항목을 선택 해제 했습니다.", selectedItemCount);
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
        }
        else
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[Button] 선택 항목이 없습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
        }
    }

    void MyItemViewPage::AddButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        auto items = Items();
        auto selectedItems = ItemGridView().SelectedItems();
        auto selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 1)
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[AddButton] 한 개의 항목을 선택 하십시오.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
        }
        else if (selectedItemCount == 1)
        {
			auto item = selectedItems.GetAt(0).as<MyApp::MyItem>();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarSeverity = InfoBarSeverity::Error;
                inforBarMessage = std::format(L"[AddButton] 항목을 찾을 수 없습니다.");
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
            }
            else
            {
                inforBarSeverity = InfoBarSeverity::Success;
                inforBarMessage = std::format(L"[AddButton] {}번째 항목 뒤에 추가합니다.", itemPosition + 1);
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);


                AddItem(itemPosition + 1);
            }
        }
        else if (selectedItemCount == 0)
        {
            inforBarSeverity = InfoBarSeverity::Success;
            inforBarMessage = std::format(L"[AddButton] 맨 막지막 위치에 추가합니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);


            AddItem(Items().Size());
        }
    }

    void MyItemViewPage::EditButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        auto items = Items();
        auto selectedItems = ItemGridView().SelectedItems();
        auto selectedItemCount = selectedItems.Size();
        if (selectedItemCount > 1)
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[EditButton] 한 개의 항목을 선택 하십시오.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
        }
        else if (selectedItemCount == 1)
        {
            auto item = selectedItems.GetAt(0).as<MyApp::MyItem>();
            uint32_t itemPosition = 0;
            auto found = items.IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarSeverity = InfoBarSeverity::Error;
                inforBarMessage = std::format(L"[EditButton] 항목을 찾을 수 없습니다.");
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
            }
            else
            {
                inforBarSeverity = InfoBarSeverity::Success;
                inforBarMessage = std::format(L"[EditButton] {}번째 항목을 편집합니다.", itemPosition + 1);
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);


                EditItem(itemPosition);
            }
        }
        else if (selectedItemCount == 0)
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[EditButton] 선택 항목이 없습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
        }
    }

    void MyItemViewPage::AddItem(uint32_t position)
    {
        MyApp::MyItem item;
        item.Title(L"제목");
        item.Subtitle(L"부제목");
        item.Description(L"설명");
        
        if (position >= Items().Size())
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
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        if (position >= Items().Size())
        {
            inforBarSeverity = InfoBarSeverity::Error;
            inforBarMessage = std::format(L"[Edit] 항목의 위치가 잘못되었습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
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
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        auto selectedItems = ItemGridView().SelectedItems();
        uint32_t selectedItemCount = selectedItems.Size();
        if (selectedItemCount == 0)
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[DeleteButton] 항목을 선택 하십시오.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
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
			auto found = Items().IndexOf(item, itemPosition);
            if (!found)
            {
                inforBarSeverity = InfoBarSeverity::Error;
                inforBarMessage = std::format(L"[DeleteButton] 항목을 찾을 수 없습니다. : {}", item.Title());
                _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
			}
            else
            {
                Items().RemoveAt(itemPosition);
            }
        }


        ItemGridView().SelectedItems().Clear();
        ItemCountTextBlock_Update();


        inforBarSeverity = InfoBarSeverity::Success;
        inforBarMessage = std::format(L"[DeleteButton] {}개 항목을 삭제했습니다.", selectedItemCount);
        _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
    }

    void MyItemViewPage::DeleteAllButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;


        auto items = Items();
        uint32_t itemCount = items.Size();
        if (itemCount == 0)
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[DeleteAllButton] 대상 항목이 비었습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
        }
        else
        {
            items.Clear();
            ItemGridView().SelectedItems().Clear();
            ItemCountTextBlock_Update();

            inforBarSeverity = InfoBarSeverity::Success;
            inforBarMessage = std::format(L"[DeleteAllButton] {}개 항목을 삭제했습니다.", itemCount);
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
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
        InfoBarSeverity inforBarSeverity;
        std::wstring inforBarMessage;

        
        std::wstring keyword = FindTextBox().Text().c_str();
        if (keyword.empty())
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[FindButton] 검색어가 비어 있습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
            return;
        }


        auto items = Items();
        uint32_t itemCount = items.Size();
        if (itemCount == 0)
        {
            inforBarSeverity = InfoBarSeverity::Warning;
            inforBarMessage = std::format(L"[FindButton] 대상 항목이 비었습니다.");
            _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
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
                    inforBarSeverity = InfoBarSeverity::Error;
                    inforBarMessage = std::format(L"[FindButton] 검색 할 항목을 찾을 수 없습니다. : {}", item.Title());
                    _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);
                }
                else
                {
                    inforBarSeverity = InfoBarSeverity::Success;
                    inforBarMessage = std::format(L"[FindButton] {}번쨰 항목 위치에 \'{}\'에 해당하는 항목을 찾았습니다.",
						itemPosition + 1, keyword
                    );
                    _MainPage.NotifyUser(inforBarMessage, inforBarSeverity);


                    ItemGridView().ScrollIntoView(item);


                    //auto rowHeight = ItemGridView_GetItemRowHeight(itemPosition) + 4.0;
                    //ItemGridViewScrollViewer().ChangeView(nullptr, static_cast<double>(36.0 + (itemPosition) * rowHeight), nullptr);
                }
                break;
			}            
        }
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
		//std::size_t itemCount = MyViewModel::Instance().Items().Size();
        std::size_t itemCount = Items().Size();

		std::wstring message = std::format(L"항목: {} 개", itemCount);
        ItemCountTextBlock().Text(message.c_str());
    }
}

