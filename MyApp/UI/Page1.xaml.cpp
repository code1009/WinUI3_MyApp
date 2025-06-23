#include "pch.h"

//#include <inspectable.h>
//#include <Unknwn.h>
//#include <DispatcherQueue.h>
//#include <shobjidl.h>

//#undef GetCurrentTime
//
//#include <winrt/Windows.Foundation.h>
//#include <winrt/Windows.Foundation.Collections.h>
//#include <winrt/Windows.Storage.h>
//#include <winrt/Windows.Storage.Pickers.h>
//#include <winrt/Windows.System.h>

//#include <ShObjidl_core.h>

#include <winrt/Windows.Storage.Pickers.h>

//#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h> // For IWindowNative
//#include "microsoft.ui.xaml.window.h" 

#include "Page1.xaml.h"

#if __has_include("Page1.g.cpp")

#include "Page1.g.cpp"

#endif

#include "NavigationParam.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
//using namespace Windows::Foundation;

namespace winrt::MyApp::implementation
{
    Page1::Page1()
    {
        InitializeComponent();

        this->Loaded({ this, &Page1::Page_Loaded });
        this->Unloaded({ this, &Page1::Page_Unloaded });
    }

    
    void Page1::Page_Loaded(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
#if 1
        if (!_DispatcherTimer)
        {
            _DispatcherTimer = Microsoft::UI::Xaml::DispatcherTimer();
            _DispatcherTimer.Interval(std::chrono::seconds(1));
            //_DispatcherTimer.Interval(std::chrono::milliseconds(1));
            _DispatcherTimer.Tick(
                { this, &Page1::DispatcherTimer_OnTick }
            );
        }
        _TickCount = 0;
        _DispatcherTimer.Start();
#endif
    }

    void Page1::Page_Unloaded(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        if (_DispatcherTimer)
        {
            _DispatcherTimer.Stop();
        }
    }
    void Page1::DispatcherTimer_OnTick(IInspectable const& /*sender*/, IInspectable const& /*eventArgs*/)
    {
        _TickCount++;

        Title().Text(winrt::to_hstring(_TickCount) + L"초 경과");
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

    winrt::Windows::Foundation::IAsyncAction Page1::CustomDialog_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
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
            message += L"CustomDialog의 Primary 버튼이 눌렸습니다.\n입력 값 = ";
            message += dialog.Input();
            _MainPage.NotifyUser(message.c_str(), InfoBarSeverity::Success);
            co_return;

        case ContentDialogResult::Secondary:
            message += L"CustomDialog의 Secondary 버튼이 눌렸습니다.\n입력 값 = ";
            message += dialog.Input();
            _MainPage.NotifyUser(message.c_str(), InfoBarSeverity::Success);
            co_return;

        case ContentDialogResult::None:
            message += L"CustomDialog의 Close 버튼이 눌렸습니다.\n입력 값 = ";
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

    winrt::Windows::Foundation::IAsyncAction Page1::ContentDialog_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        ContentDialog dialog;
        dialog.XamlRoot(_MainPage.XamlRoot());
        dialog.Title(box_value(L"컨텐트다이얼로그"));
        dialog.Content(box_value(L"확인 또는 취소 버튼 누르세요."));
        dialog.PrimaryButtonText(L"확인");
        dialog.CloseButtonText(L"취소");
        dialog.DefaultButton(ContentDialogButton::Close);
        const auto result = co_await dialog.ShowAsync();
        if (result != ContentDialogResult::Primary)
        {
            co_return;
        }

        std::wstring message = L"ContentDialog의 Primary 버튼이 눌렸습니다.";
        _MainPage.NotifyUser(message.c_str(), InfoBarSeverity::Success);
    }

    // https://github.com/microsoft/FFmpegInterop/blob/main/Samples/MediaPlayerCPP/MainPage.cpp
    // https://github.com/MarkIngramUK/XamlIslands/blob/9a260595c5a9736a825672e9f2e89f1b5d87fae0/Common/Sample.hpp

#if 0
    // IWindowNative 인터페이스 정의 (WinUI 3 Desktop)
    struct __declspec(uuid("6d5140c1-7436-11ce-8034-00aa006009fa")) IWindowNative : ::IUnknown
    {
        virtual HRESULT __stdcall get_WindowHandle(HWND* hwnd) = 0;
    };
#endif

#if 0
    // Page 또는 MainPage에서 HWND 얻기
    HWND GetWindowHandleFromXamlRoot(Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
        auto window = xamlRoot.Content().XamlRoot().Content().as<winrt::Microsoft::UI::Xaml::Window>();
        auto windowNative = window.as<IWindowNative>();
        HWND hwnd = nullptr;
        windowNative->get_WindowHandle(&hwnd);
        return hwnd;
    }

    // 또는 Window::Current() 사용
    HWND GetWindowHandleFromWindow()
    {
        auto window = winrt::Microsoft::UI::Xaml::Window::Current();
        auto windowNative = window.as<IWindowNative>();
        HWND hwnd = nullptr;
        windowNative->get_WindowHandle(&hwnd);
        return hwnd;
    }
#endif

#if 0

// pch 확인
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <shobjidl.h> // For FileOpenPicker, FileSavePicker, FolderPicker
#include <Unknwn.h>

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime

#include <restrictederrorinfo.h>
#include <hstring.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.UI.Xaml.Interop.h> //For using xaml_typename

#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Media.Animation.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Windows.UI.Core.h>

#endif


    winrt::Windows::Foundation::IAsyncAction Page1::FileOpenPicker_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        HWND hwnd = nullptr;
        //hwnd = GetWindowHandleFromWindow();
		//hwnd = GetWindowHandleFromXamlRoot(_MainPage.XamlRoot());
        hwnd = reinterpret_cast<HWND>(MyViewModel::Instance().MainWindowHandle());


        using namespace winrt::Windows::Storage::Pickers;
        using namespace winrt::Windows::Storage;
        using namespace winrt::Windows::System;


        winrt::Windows::Storage::Pickers::FileOpenPicker picker;
        picker.as<::IInitializeWithWindow>()->Initialize(hwnd);


        picker.ViewMode(PickerViewMode::Thumbnail);
        //picker.ViewMode(PickerViewMode::List);
        picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        picker.FileTypeFilter().Append(L".txt");
        picker.FileTypeFilter().Append(L".png");
        picker.FileTypeFilter().Append(L".jpg");


        StorageFile file = co_await picker.PickSingleFileAsync();
        if (file)
        {
            _MainPage.NotifyUser((L"선택된 파일: " + file.Name()).c_str(), InfoBarSeverity::Success);
        }
        else
        {
            _MainPage.NotifyUser(L"파일이 선택되지 않았습니다.", InfoBarSeverity::Warning);
        }
    }

    winrt::Windows::Foundation::IAsyncAction Page1::FileSavePicker_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        HWND hwnd = nullptr;
        hwnd = reinterpret_cast<HWND>(MyViewModel::Instance().MainWindowHandle());


        using namespace winrt::Windows::Storage::Pickers;
        using namespace winrt::Windows::Storage;
        using namespace winrt::Windows::System;


        FileSavePicker picker;
        picker.as<IInitializeWithWindow>()->Initialize(hwnd);


        picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        picker.FileTypeChoices().Insert(L"텍스트 파일", single_threaded_vector<hstring>({ L".txt" }));
        picker.SuggestedFileName(L"NewDocument");


        StorageFile file = co_await picker.PickSaveFileAsync();
        if (file)
        {
            _MainPage.NotifyUser((L"저장할 파일: " + file.Name()).c_str(), InfoBarSeverity::Success);
        }
        else
        {
            _MainPage.NotifyUser(L"저장 파일이 선택되지 않았습니다.", InfoBarSeverity::Warning);
        }
    }

    winrt::Windows::Foundation::IAsyncAction Page1::FolderPicker_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        HWND hwnd = nullptr;
        hwnd = reinterpret_cast<HWND>(MyViewModel::Instance().MainWindowHandle());


        using namespace winrt::Windows::Storage::Pickers;
        using namespace winrt::Windows::Storage;
        using namespace winrt::Windows::System;


        FolderPicker picker;
#if WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
        picker.as<IInitializeWithWindow>()->Initialize(hwnd);
#endif


        picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        //picker.FileTypeFilter().Append(L"*");


        StorageFolder folder = co_await picker.PickSingleFolderAsync();
        if (folder)
        {
            _MainPage.NotifyUser((L"선택된 폴더: " + folder.Name()).c_str(), InfoBarSeverity::Success);
        }
        else
        {
            _MainPage.NotifyUser(L"폴더가 선택되지 않았습니다.", InfoBarSeverity::Warning);
        }
    }
}
