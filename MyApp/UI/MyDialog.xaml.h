#pragma once

#include "MyDialog.g.h"

namespace winrt::MyApp::implementation
{
    struct MyDialog : MyDialogT<MyDialog>
    {
    private:
		hstring _Input;

    public:
        MyDialog();
        virtual ~MyDialog();

    public:
        hstring Input();
		void Input(hstring const& value);

    public:
        void MyDialog_PrimaryButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& eventArgs);
        void MyDialog_CloseButtonClick(winrt::Microsoft::UI::Xaml::Controls::ContentDialog const& sender, winrt::Microsoft::UI::Xaml::Controls::ContentDialogButtonClickEventArgs const& eventArgs);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MyDialog : MyDialogT<MyDialog, implementation::MyDialog>
    {
    };
}
