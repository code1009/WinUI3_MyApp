#include "pch.h"

#include "MyDialog.xaml.h"

#if __has_include("MyDialog.g.cpp")

#include "MyDialog.g.cpp"

#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace Windows::Foundation;

namespace winrt::MyApp::implementation
{
    MyDialog::MyDialog()
    {
        InitializeComponent();

		OutputDebugStringW(L"MyDialog\n");

		Input(L"MyDialog");
    }

    MyDialog::~MyDialog()
    {
        OutputDebugStringW(L"~MyDialog\n");
    }

    hstring MyDialog::Input()
    {
        return _Input;
	}

    void MyDialog::Input(hstring const& value)
    {
		_Input = value;
    }

    void MyDialog::MyDialog_PrimaryButtonClick(ContentDialog const& /*sender*/, ContentDialogButtonClickEventArgs const& /*eventArgs*/)
    {
        std::wstring message;
        std::wstring input;
        input = InputTextBox().Text();
        message = L"PrimaryButton Clicked: " + input;
		Input(message.c_str());
    }

    void MyDialog::MyDialog_CloseButtonClick(ContentDialog const& /*sender*/, ContentDialogButtonClickEventArgs const& /*eventArgs*/)
    {
        std::wstring message;
        std::wstring input;
        input = InputTextBox().Text();
        message = L"CloseButton Clicked: " + input;
        Input(message.c_str());
    }
}
