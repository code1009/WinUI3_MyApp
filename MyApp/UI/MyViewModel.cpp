﻿#include "pch.h"
#include "MyViewModel.h"
#include "MyViewModel.g.cpp"

// WARNING: This file is automatically generated by a tool. Do not directly
// add this file to your project, as any changes you make will be lost.
// This file is a stub you can use as a starting point for your implementation.
//
// To add a copy of this file to your project:
//   1. Copy this file from its original location to the location where you store 
//      your other source files (e.g. the project root). 
//   2. Add the copied file to your project. In Visual Studio, you can use 
//      Project -> Add Existing Item.
//   3. Delete this comment and the 'static_assert' (below) from the copied file.
//      Do not modify the original file.
//
// To update an existing file in your project:
//   1. Copy the relevant changes from this file and merge them into the copy 
//      you made previously.
//    
// This assertion helps prevent accidental modification of generated files.
//static_assert(false, "This file is generated by a tool and will be overwritten. Open this error and view the comment for assistance.");

namespace winrt::MyApp::implementation
{
    winrt::MyApp::MyViewModel MyViewModel::Instance()
    {
		static winrt::MyApp::MyViewModel instance;

        return instance;
    }

    MyViewModel::MyViewModel()
    {
        OutputDebugStringW(L"MyViewModel\n");


        _Items = winrt::single_threaded_observable_vector<MyApp::MyItem>();


        winrt::MyApp::MyItem item;
        for(std::size_t i = 0; i < 200; i++)
        {
            item = winrt::make<winrt::MyApp::implementation::MyItem>();
            item.Title(L"제목" + std::to_wstring(i + 1));
            item.Subtitle(L"부제목" + std::to_wstring(i + 1));
            item.Description(L"설명" + std::to_wstring(i + 1));
            _Items.Append(item);
		}
    }

    MyViewModel::~MyViewModel()
    {
		OutputDebugStringW(L"~MyViewModel\n");
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::MyApp::MyItem> MyViewModel::Items()
    {
        OutputDebugStringW(L"MyViewModel.Items\n");
        return _Items;
    }
}
