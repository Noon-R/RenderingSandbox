// ライブラリ動作確認用テストコード
// このファイルは動作確認のための一時的なテストコードです

#include "Tests/TestImGui.h"
#include "Tests/TestStb.h"
#include "Tests/TestAssimp.h"

// Logger
#include "Logger/Logger.h"
#include "Logger/ConsoleSink.h"
#include "Logger/DebugOutputSink.h"
#include "Logger/FileSink.h"
#include "Logger/LogMacros.h"

#include <iostream>
#include <wrl.h>

#define WIN32_LEAN_AND_MEAN //不要な機能をWindows.hから除外するための定義
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
extern "C" {

    __declspec(dllexport)
        extern const UINT D3D12SDKVersion = D3D12_SDK_VERSION;
    __declspec(dllexport)
        extern const char8_t* D3D12SDKPath = u8".\\D3D12\\";

}

using namespace Microsoft::WRL;

int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    // コンソールウィンドウを割り当て（Windows Subsystemでもコンソール表示可能にする）
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    // Logger初期化
    auto& logger = RenderingSandbox::Logger::GetInstance();

    // 複数のSinkを追加
    logger.AddSink(std::make_unique<RenderingSandbox::ConsoleSink>());
    logger.AddSink(std::make_unique<RenderingSandbox::DebugOutputSink>());
    logger.AddSink(std::make_unique<RenderingSandbox::FileSink>("RenderingSandbox.log"));

#ifdef _DEBUG
    logger.SetGlobalMinLevel(RenderingSandbox::LogLevel::Trace);
#else
    logger.SetGlobalMinLevel(RenderingSandbox::LogLevel::Info);
#endif

    LOG_INFO("System", "=== RenderingSandbox Started ===");
    LOG_INFO("System", "");

    std::cout << "=== Library Test ===" << std::endl;
    std::cout << std::endl;

    // ImGuiテスト実行
    RunImGuiTest();

    // stbテスト実行
    RunStbTest();

    // Assimpテスト実行
    RunAssimpTest();

    std::cout << "=== All Library Tests Completed ===" << std::endl;
    std::cout << std::endl;

    // DirectX12の初期化
    HRESULT hr;
    UINT dxgiFlags = 0;

#if _DEBUG
    //TODO: 単純なデバッグ起動ではなく、DebugLevelを起動時引数で指定して変えられるようにする

    ComPtr<ID3D12Debug> d3d12Debug;
    //SUCCEEDEDマクロはHRESULTを受けて成功しているかを判定してくれる
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&d3d12Debug))))
    {
        //DebugLayerの有効化 (APIの不正利用などを検出できるようにする)
        d3d12Debug->EnableDebugLayer();
        LOG_INFO("D3D12", "Debug Layer enabled.");

        //GBVのの有効化(Debug情報の追加)
        //GPU Based Validation
        ComPtr<ID3D12Debug3> debug3;
        d3d12Debug.As(&debug3);
        if (debug3) {
            debug3->SetEnableGPUBasedValidation(TRUE);
            LOG_INFO("D3D12", "GPU Based Validation enabled.");
        }
    }
    else
    {
        LOG_ERROR("D3D12", "Failed to enable Debug Layer.");
    }
#endif
    ComPtr<IDXGIAdapter1> adapter;

    //DXGIの作成
    //DXGIが低レベル層との懸け橋になってくれることで、ハードウェアの違いを吸収してくれる
    //更新などの緩衝材にもなっているはず...?
    //ここからdxgi1_6が必要になってくる
    ComPtr<IDXGIFactory7> _dxgiFactory;
    hr = CreateDXGIFactory2(dxgiFlags, IID_PPV_ARGS(&_dxgiFactory));
    LOG_HRESULT("D3D12", hr, "Failed to create DXGI Factory");

    //デバイスの検索と作成
    
    //Adapterの列挙
    //Adapter: GPU1つに対してあるようなものほぼGPUドライバに近い
    UINT adapterIndex = 0;
    //EnumAdapter1はGPUが今使われているかに関係なくあるものを列挙して
    //EnumAdapterは使われているものだけを列挙するっぽい
    while (DXGI_ERROR_NOT_FOUND != _dxgiFactory->EnumAdapters1(adapterIndex, &adapter))
    {
        DXGI_ADAPTER_DESC1 desc1{};
        adapter->GetDesc1(&desc1);
        ++adapterIndex;

        //"Microsoft Basic Render Driver"が常駐しているので除外する
        if (desc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            continue;
        }

        //D3D12の利用可否の確認
        hr = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), nullptr);
        LOG_HRESULT("D3D12", hr, "D3D12 device availability check");
        if (SUCCEEDED(hr))
        {
            break;
        }
    }

    


    std::cout << "Press Enter to exit...";
    std::cin.get();

    LOG_INFO("System", "=== RenderingSandbox Terminated ===");
    logger.Flush();

    // コンソールウィンドウを解放
    FreeConsole();

    return 0;
}
