#include "pch.h"
#include "MyCustomControl.h"
#if __has_include("MyCustomControl.g.cpp")
#include "MyCustomControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::MyApp::implementation
{
    MyCustomControl::MyCustomControl()
    {
        DefaultStyleKey(winrt::box_value(L"MyApp.MyCustomControl"));

        // 생성자에는 동작이 안됨
        if (auto border = GetTemplateChild(L"MyBorder").try_as<Border>())
        {
            border.Height(100);
            border.Width(100);

            winrt::Windows::UI::Color bkColor;

            bkColor = winrt::Windows::UI::Colors::Red();
            border.Background(SolidColorBrush(bkColor));
            border.BorderThickness(
                ThicknessHelper::FromLengths(2.0, 2.0, 2.0, 2.0)
            );
        }

        this->Loaded({ this, &MyCustomControl::Control_Loaded });
        this->Unloaded({ this, &MyCustomControl::Control_Unloaded });
    }

    void MyCustomControl::Control_Loaded(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
        if (auto border = GetTemplateChild(L"MyBorder").try_as<Border>())
        {
            //border.Height(10);
            //border.Width(10);

            winrt::Windows::UI::Color bkColor;

            bkColor = winrt::Windows::UI::Colors::Blue();
            
            //border.Background(SolidColorBrush(bkColor));

            border.BorderThickness(
                ThicknessHelper::FromLengths(2.0, 2.0, 2.0, 2.0)
            );
        }

        /*
        동작 안됨
        this->Background(
            SolidColorBrush(winrt::Windows::UI::Colors::Yellow())
		);
        */
    }

    void MyCustomControl::Control_Unloaded(IInspectable const& /*sender*/, RoutedEventArgs const& /*eventArgs*/)
    {
    }

    winrt::Windows::UI::Color MyCustomControl::BackgroundColor()
    {
        return _BackgroundColor;
    }

    void MyCustomControl::BackgroundColor(winrt::Windows::UI::Color const& value)
    {
        _BackgroundColor = value;
        if (auto border = GetTemplateChild(L"MyBorder").try_as<Border>())
        {
            //Background와 BackgroundColor 왜 둘다 안될까....
            //border.Background(SolidColorBrush(value));
        }
    }
}
