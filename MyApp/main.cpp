#include "pch.h"
#include <windows.h>
#include "UI/App.xaml.h"

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    //winrt::init_apartment(winrt::apartment_type::multi_threaded); // 한국어 입력 안됨(ms-bug?)

    ::winrt::Microsoft::UI::Xaml::Application::Start(
        [](auto&&)
        {
            ::winrt::make<::winrt::MyApp::implementation::App>();
        });

    return 0;
}
