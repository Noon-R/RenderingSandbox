# DXGI アダプタ情報取得ガイド

## 概要

DXGIを使用してGPU（グラフィックスアダプタ）の詳細情報を取得する方法を解説します。このドキュメントでは、ベンダー情報、デバイス情報、ドライバーバージョン、メモリ情報などの取得方法を説明します。

---

## 📋 目次

1. [DXGI_ADAPTER_DESC1による基本情報取得](#dxgi_adapter_desc1による基本情報取得)
2. [ベンダー情報の取得と解釈](#ベンダー情報の取得と解釈)
3. [ドライバーバージョンの取得](#ドライバーバージョンの取得)
4. [詳細なメモリ情報の取得（IDXGIAdapter4）](#詳細なメモリ情報の取得idxgiadapter4)
5. [実装例](#実装例)
6. [注意点とトラブルシューティング](#注意点とトラブルシューティング)

---

## DXGI_ADAPTER_DESC1による基本情報取得

### 概要

`DXGI_ADAPTER_DESC1`構造体は、グラフィックスアダプタの基本的な情報を提供します。

### 構造体定義

```cpp
typedef struct DXGI_ADAPTER_DESC1 {
    WCHAR  Description[128];      // GPU名（例: "NVIDIA GeForce RTX 4090"）
    UINT   VendorId;              // ベンダーID（例: 0x10DE = NVIDIA）
    UINT   DeviceId;              // デバイスID（GPUモデル固有）
    UINT   SubSysId;              // サブシステムID（マザーボード/カード固有）
    UINT   Revision;              // リビジョン番号
    SIZE_T DedicatedVideoMemory;  // 専用ビデオメモリ（バイト）
    SIZE_T DedicatedSystemMemory; // 専用システムメモリ（バイト）
    SIZE_T SharedSystemMemory;    // 共有システムメモリ（バイト）
    LUID   AdapterLuid;           // アダプタの一意識別子
    UINT   Flags;                 // フラグ（DXGI_ADAPTER_FLAG）
} DXGI_ADAPTER_DESC1;
```

### 取得方法

```cpp
ComPtr<IDXGIAdapter1> adapter;
DXGI_ADAPTER_DESC1 desc;

// アダプタの記述情報を取得
HRESULT hr = adapter->GetDesc1(&desc);
if (SUCCEEDED(hr)) {
    // 情報を使用
}
```

### 一次ソース

- [DXGI_ADAPTER_DESC1 structure](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc1)
- [IDXGIAdapter1::GetDesc1 method](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter1-getdesc1)

---

## ベンダー情報の取得と解釈

### VendorID一覧

主要なGPUベンダーのVendorIDは以下の通りです：

| ベンダー名 | VendorID (16進数) | VendorID (10進数) |
|-----------|-------------------|-------------------|
| AMD | 0x1002 | 4098 |
| NVIDIA | 0x10DE | 4318 |
| Intel | 0x8086 | 32902 |
| Microsoft (WARP) | 0x1414 | 5140 |
| Qualcomm | 0x5143 | 4634 |
| ARM | 0x13B5 | 5348 |

### ベンダー名取得ヘルパー関数

```cpp
/// <summary>
/// VendorIDからベンダー名を取得
/// </summary>
/// <param name="vendorId">DXGI_ADAPTER_DESC1.VendorId</param>
/// <returns>ベンダー名文字列</returns>
const char* GetVendorName(UINT vendorId) {
    switch (vendorId) {
        case 0x1002: return "AMD";
        case 0x10DE: return "NVIDIA";
        case 0x8086: return "Intel";
        case 0x1414: return "Microsoft (WARP)";
        case 0x5143: return "Qualcomm";
        case 0x13B5: return "ARM";
        default:     return "Unknown";
    }
}
```

### DeviceIDの意味

DeviceIDはGPUモデルを識別します。例：

- NVIDIA GeForce RTX 4090: `0x2684`
- NVIDIA GeForce RTX 4080: `0x2704`
- AMD Radeon RX 7900 XTX: `0x744C`

DeviceIDからGPUモデル名への変換は、ベンダー固有のデータベースが必要です。

### GPU名の取得

```cpp
DXGI_ADAPTER_DESC1 desc;
adapter->GetDesc1(&desc);

// WCHAR配列からstd::stringへの変換
std::wstring wDescription(desc.Description);
std::string gpuName(wDescription.begin(), wDescription.end());

// または、より安全な変換
size_t convertedChars = 0;
char gpuNameBuffer[128];
wcstombs_s(&convertedChars, gpuNameBuffer, desc.Description, _TRUNCATE);
```

---

## ドライバーバージョンの取得

### CheckInterfaceSupportメソッド（推奨）

最も標準的な方法で、UMD（User Mode Driver）のバージョンを取得できます。

#### 基本的な使用方法

```cpp
#include <dxgi.h>
#include <d3d11.h>  // IDXGIDeviceの定義に必要

ComPtr<IDXGIAdapter1> adapter;
LARGE_INTEGER umdVersion;

HRESULT hr = adapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &umdVersion);
if (SUCCEEDED(hr)) {
    // バージョン情報の解析
    UINT64 encodedVersion = umdVersion.QuadPart;

    // バージョン番号の抽出
    // 形式: Product.Version.SubVersion.Build
    UINT16 product    = (encodedVersion >> 48) & 0xFFFF;
    UINT16 version    = (encodedVersion >> 32) & 0xFFFF;
    UINT16 subVersion = (encodedVersion >> 16) & 0xFFFF;
    UINT16 build      = encodedVersion & 0xFFFF;

    printf("Driver Version: %u.%u.%u.%u\n",
           product, version, subVersion, build);
}
```

#### バージョン番号の構造

LARGE_INTEGER（64ビット）の内訳：

```
Bits 63-48: Product    (製品バージョン)
Bits 47-32: Version    (メジャーバージョン)
Bits 31-16: SubVersion (マイナーバージョン)
Bits 15-0:  Build      (ビルド番号)
```

#### 出力例

```
Driver Version: 31.0.15.3742   (NVIDIA)
Driver Version: 30.0.15063.0   (AMD)
Driver Version: 10.0.22621.0   (Intel)
```

### 一次ソース

- [IDXGIAdapter::CheckInterfaceSupport method](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter-checkinterfacesupport)

### 注意事項

#### ⚠️ Windows 10以降の動作

- Windows 10以降では、セキュリティ上の理由から常に成功するとは限りません
- 一部のドライバーでは対応していない場合があります
- **必ず`SUCCEEDED(hr)`をチェックしてください**

#### ⚠️ 代替方法：WMI

CheckInterfaceSupportが失敗する場合、WMI（Windows Management Instrumentation）を使用できますが、実装が複雑になります：

```cpp
// WMIを使った代替方法（概要のみ）
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

// 実装は複雑なため、基本的にはCheckInterfaceSupportを推奨
// WMIクエリ例: "SELECT * FROM Win32_VideoController"
```

---

## 詳細なメモリ情報の取得（IDXGIAdapter4）

### 概要

IDXGIAdapter4（DXGI 1.6、Windows 10 1803+）を使用すると、より詳細なビデオメモリ情報を取得できます。

### QueryVideoMemoryInfoメソッド

```cpp
ComPtr<IDXGIAdapter1> adapter1;
ComPtr<IDXGIAdapter4> adapter4;

// IDXGIAdapter4へのキャスト
HRESULT hr = adapter1.As(&adapter4);
if (SUCCEEDED(hr)) {
    DXGI_QUERY_VIDEO_MEMORY_INFO memoryInfo = {};

    hr = adapter4->QueryVideoMemoryInfo(
        0,  // NodeIndex (通常は0)
        DXGI_MEMORY_SEGMENT_GROUP_LOCAL,  // ローカルメモリ（VRAM）
        &memoryInfo
    );

    if (SUCCEEDED(hr)) {
        printf("Video Memory Budget: %llu MB\n",
               memoryInfo.Budget / (1024 * 1024));
        printf("Current Usage: %llu MB\n",
               memoryInfo.CurrentUsage / (1024 * 1024));
        printf("Available for Reservation: %llu MB\n",
               memoryInfo.AvailableForReservation / (1024 * 1024));
        printf("Current Reservation: %llu MB\n",
               memoryInfo.CurrentReservation / (1024 * 1024));
    }
}
```

### DXGI_QUERY_VIDEO_MEMORY_INFO構造体

```cpp
typedef struct DXGI_QUERY_VIDEO_MEMORY_INFO {
    UINT64 Budget;                    // OS割り当て予算
    UINT64 CurrentUsage;              // 現在の使用量
    UINT64 AvailableForReservation;   // 予約可能量
    UINT64 CurrentReservation;        // 現在の予約量
} DXGI_QUERY_VIDEO_MEMORY_INFO;
```

### メモリセグメントグループ

```cpp
typedef enum DXGI_MEMORY_SEGMENT_GROUP {
    DXGI_MEMORY_SEGMENT_GROUP_LOCAL = 0,      // VRAM（専用ビデオメモリ）
    DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1   // システムメモリ
} DXGI_MEMORY_SEGMENT_GROUP;
```

### 一次ソース

- [IDXGIAdapter4::QueryVideoMemoryInfo method](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nf-dxgi1_6-idxgiadapter4-queryvideomemoryinfo)
- [DXGI_QUERY_VIDEO_MEMORY_INFO structure](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/ns-dxgi1_4-dxgi_query_video_memory_info)

---

## 実装例

### 基本的なアダプタ情報表示

```cpp
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3d11.h>  // IDXGIDevice用
#include <wrl.h>
#include <iostream>
#include <format>

using Microsoft::WRL::ComPtr;

/// <summary>
/// VendorIDからベンダー名を取得
/// </summary>
const char* GetVendorName(UINT vendorId) {
    switch (vendorId) {
        case 0x1002: return "AMD";
        case 0x10DE: return "NVIDIA";
        case 0x8086: return "Intel";
        case 0x1414: return "Microsoft (WARP)";
        case 0x5143: return "Qualcomm";
        case 0x13B5: return "ARM";
        default:     return "Unknown";
    }
}

/// <summary>
/// アダプタ情報を詳細に表示
/// </summary>
void PrintAdapterInfo(IDXGIAdapter1* adapter) {
    DXGI_ADAPTER_DESC1 desc;
    HRESULT hr = adapter->GetDesc1(&desc);
    if (FAILED(hr)) {
        std::cerr << "Failed to get adapter description" << std::endl;
        return;
    }

    // GPU名の取得
    std::wstring wGpuName(desc.Description);
    std::string gpuName(wGpuName.begin(), wGpuName.end());

    // 基本情報の表示
    std::cout << "========================================" << std::endl;
    std::cout << "GPU Information" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::format("Name: {}\n", gpuName);
    std::cout << std::format("Vendor: {} (0x{:04X})\n",
                             GetVendorName(desc.VendorId), desc.VendorId);
    std::cout << std::format("Device ID: 0x{:04X}\n", desc.DeviceId);
    std::cout << std::format("SubSystem ID: 0x{:08X}\n", desc.SubSysId);
    std::cout << std::format("Revision: {}\n", desc.Revision);

    // メモリ情報
    std::cout << "\nMemory Information:" << std::endl;
    std::cout << std::format("  Dedicated Video Memory: {} MB\n",
                             desc.DedicatedVideoMemory / (1024 * 1024));
    std::cout << std::format("  Dedicated System Memory: {} MB\n",
                             desc.DedicatedSystemMemory / (1024 * 1024));
    std::cout << std::format("  Shared System Memory: {} MB\n",
                             desc.SharedSystemMemory / (1024 * 1024));

    // ドライバーバージョンの取得
    LARGE_INTEGER umdVersion;
    hr = adapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &umdVersion);
    if (SUCCEEDED(hr)) {
        UINT64 encodedVersion = umdVersion.QuadPart;
        UINT16 product    = (encodedVersion >> 48) & 0xFFFF;
        UINT16 version    = (encodedVersion >> 32) & 0xFFFF;
        UINT16 subVersion = (encodedVersion >> 16) & 0xFFFF;
        UINT16 build      = encodedVersion & 0xFFFF;

        std::cout << std::format("\nDriver Version: {}.{}.{}.{}\n",
                                 product, version, subVersion, build);
    } else {
        std::cout << "\nDriver Version: Not available" << std::endl;
    }

    // フラグ情報
    std::cout << "\nFlags:" << std::endl;
    if (desc.Flags & DXGI_ADAPTER_FLAG_REMOTE) {
        std::cout << "  - Remote adapter" << std::endl;
    }
    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
        std::cout << "  - Software adapter" << std::endl;
    }
    if (desc.Flags == 0) {
        std::cout << "  - Hardware adapter" << std::endl;
    }

    std::cout << "========================================" << std::endl;
}
```

### IDXGIAdapter4を使った詳細情報表示

```cpp
/// <summary>
/// 詳細なメモリ情報を表示（IDXGIAdapter4使用）
/// </summary>
void PrintDetailedMemoryInfo(IDXGIAdapter1* adapter) {
    ComPtr<IDXGIAdapter4> adapter4;
    HRESULT hr = adapter->QueryInterface(IID_PPV_ARGS(&adapter4));

    if (FAILED(hr)) {
        std::cout << "IDXGIAdapter4 not supported (requires Windows 10 1803+)"
                  << std::endl;
        return;
    }

    // ローカルメモリ（VRAM）情報
    DXGI_QUERY_VIDEO_MEMORY_INFO localMemoryInfo = {};
    hr = adapter4->QueryVideoMemoryInfo(
        0,
        DXGI_MEMORY_SEGMENT_GROUP_LOCAL,
        &localMemoryInfo
    );

    if (SUCCEEDED(hr)) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "Detailed Memory Information (Local)" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::format("Budget: {} MB\n",
                                 localMemoryInfo.Budget / (1024 * 1024));
        std::cout << std::format("Current Usage: {} MB\n",
                                 localMemoryInfo.CurrentUsage / (1024 * 1024));
        std::cout << std::format("Available for Reservation: {} MB\n",
                                 localMemoryInfo.AvailableForReservation / (1024 * 1024));
        std::cout << std::format("Current Reservation: {} MB\n",
                                 localMemoryInfo.CurrentReservation / (1024 * 1024));
    }

    // 非ローカルメモリ（システムメモリ）情報
    DXGI_QUERY_VIDEO_MEMORY_INFO nonLocalMemoryInfo = {};
    hr = adapter4->QueryVideoMemoryInfo(
        0,
        DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL,
        &nonLocalMemoryInfo
    );

    if (SUCCEEDED(hr)) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "Detailed Memory Information (Non-Local)" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::format("Budget: {} MB\n",
                                 nonLocalMemoryInfo.Budget / (1024 * 1024));
        std::cout << std::format("Current Usage: {} MB\n",
                                 nonLocalMemoryInfo.CurrentUsage / (1024 * 1024));
        std::cout << std::format("Available for Reservation: {} MB\n",
                                 nonLocalMemoryInfo.AvailableForReservation / (1024 * 1024));
        std::cout << std::format("Current Reservation: {} MB\n",
                                 nonLocalMemoryInfo.CurrentReservation / (1024 * 1024));
    }

    std::cout << "========================================" << std::endl;
}
```

### 使用例

```cpp
int main() {
    ComPtr<IDXGIFactory6> dxgiFactory;
    HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgiFactory));

    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI factory" << std::endl;
        return -1;
    }

    UINT adapterIndex = 0;
    ComPtr<IDXGIAdapter1> adapter;

    while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND) {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        // ソフトウェアアダプタをスキップ
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            ++adapterIndex;
            continue;
        }

        // 基本情報の表示
        PrintAdapterInfo(adapter.Get());

        // 詳細メモリ情報の表示
        PrintDetailedMemoryInfo(adapter.Get());

        ++adapterIndex;
    }

    return 0;
}
```

### 出力例

```
========================================
GPU Information
========================================
Name: NVIDIA GeForce RTX 4090
Vendor: NVIDIA (0x10DE)
Device ID: 0x2684
SubSystem ID: 0x46C110DE
Revision: 161

Memory Information:
  Dedicated Video Memory: 24576 MB
  Dedicated System Memory: 0 MB
  Shared System Memory: 32768 MB

Driver Version: 31.0.15.3742

Flags:
  - Hardware adapter
========================================

========================================
Detailed Memory Information (Local)
========================================
Budget: 20480 MB
Current Usage: 512 MB
Available for Reservation: 20480 MB
Current Reservation: 0 MB
========================================

========================================
Detailed Memory Information (Non-Local)
========================================
Budget: 32768 MB
Current Usage: 128 MB
Available for Reservation: 26214 MB
Current Reservation: 0 MB
========================================
```

---

## 注意点とトラブルシューティング

### ソフトウェアアダプタの除外

Microsoft Basic Render Driver（WARP）などのソフトウェアアダプタを除外するには：

```cpp
DXGI_ADAPTER_DESC1 desc;
adapter->GetDesc1(&desc);

if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
    // ソフトウェアアダプタをスキップ
    continue;
}
```

### WCHAR から std::string への変換

GPU名などのWCHAR配列を扱う際の注意点：

```cpp
// 方法1: wstring経由（簡潔だが非ASCII文字で問題が起きる可能性）
std::wstring wDescription(desc.Description);
std::string description(wDescription.begin(), wDescription.end());

// 方法2: wcstombs_s（より安全）
char descBuffer[128];
size_t convertedChars = 0;
wcstombs_s(&convertedChars, descBuffer, desc.Description, _TRUNCATE);

// 方法3: WideCharToMultiByte（完全な制御）
int size = WideCharToMultiByte(CP_UTF8, 0, desc.Description, -1,
                                nullptr, 0, nullptr, nullptr);
std::string description(size, 0);
WideCharToMultiByte(CP_UTF8, 0, desc.Description, -1,
                    &description[0], size, nullptr, nullptr);
```

### CheckInterfaceSupport の失敗

ドライバーバージョン取得に失敗する場合：

1. **Windows 10 1803以前**: 一部のドライバーで対応していない
2. **セキュリティポリシー**: 企業環境などで制限されている場合がある
3. **仮想環境**: VMware、VirtualBoxなどでは取得できないことがある

### マルチGPU環境での注意

複数のGPUが搭載されている環境では：

```cpp
// すべてのアダプタを列挙
UINT adapterIndex = 0;
while (factory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND) {
    // 各アダプタの情報を取得
    PrintAdapterInfo(adapter.Get());
    ++adapterIndex;
}

// または、高性能GPUを優先的に取得（IDXGIFactory6）
hr = factory6->EnumAdapterByGpuPreference(
    0,
    DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
    IID_PPV_ARGS(&adapter)
);
```

### メモリサイズの単位

メモリサイズはバイト単位で返されるため、適切に変換：

```cpp
// バイト → MB
size_t memoryMB = desc.DedicatedVideoMemory / (1024 * 1024);

// バイト → GB（小数点以下も表示）
double memoryGB = static_cast<double>(desc.DedicatedVideoMemory) / (1024.0 * 1024.0 * 1024.0);
std::cout << std::format("Memory: {:.2f} GB\n", memoryGB);
```

---

## 関連ドキュメント

### プロジェクト内

- [DirectX 12インターフェースバージョンガイド](./directx12-interface-versions.md)
- PROJECT_STATUS.md

### 公式リソース

- [DXGI Overview](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi)
- [IDXGIAdapter interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter)
- [IDXGIAdapter1 interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter1)
- [IDXGIAdapter4 interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgiadapter4)
- [DXGI_ADAPTER_DESC1 structure](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc1)

---

## まとめ

### 取得できる情報

| 情報 | メソッド/構造体 | OS要件 |
|-----|---------------|--------|
| GPU名 | `DXGI_ADAPTER_DESC1.Description` | Windows 7+ |
| ベンダーID | `DXGI_ADAPTER_DESC1.VendorId` | Windows 7+ |
| デバイスID | `DXGI_ADAPTER_DESC1.DeviceId` | Windows 7+ |
| 専用ビデオメモリ | `DXGI_ADAPTER_DESC1.DedicatedVideoMemory` | Windows 7+ |
| ドライバーバージョン | `IDXGIAdapter::CheckInterfaceSupport` | Windows 7+ |
| 詳細メモリ情報 | `IDXGIAdapter4::QueryVideoMemoryInfo` | Windows 10 1803+ |

### 推奨実装パターン

1. **基本情報の取得**: `DXGI_ADAPTER_DESC1`を使用
2. **ベンダー名の表示**: VendorIDから変換関数を使用
3. **ドライバーバージョン**: `CheckInterfaceSupport`を使用（失敗時は"Not available"表示）
4. **詳細メモリ情報**: Windows 10 1803+では`IDXGIAdapter4`を使用

---

## 変更履歴

- 2026-01-10: 初版作成
