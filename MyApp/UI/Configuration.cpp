﻿#include "pch.h"

#include "Configuration.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;

namespace winrt::MyApp
{
    hstring Config::FeatureName{ L"MyApp" };
	HWND Config::MainWindowHandle{ nullptr };
    ElementTheme Config::CurrentTheme{ ElementTheme::Default };
}


