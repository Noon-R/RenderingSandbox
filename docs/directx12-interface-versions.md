# DirectX 12 インターフェースバージョン選択ガイド

## 概要

DirectX 12では、機能追加に伴い新しいインターフェースバージョンがリリースされています。このドキュメントでは、各インターフェースのバージョン比較と、学習用プロジェクトにおける推奨選択について解説します。

## インターフェースバージョンの基本原則

### バージョン番号の意味

DirectX 12のインターフェースは、機能追加時に番号が増加します：
- `ID3D12Device` → `ID3D12Device1` → `ID3D12Device2` ...
- `IDXGIAdapter` → `IDXGIAdapter1` → `IDXGIAdapter2` ...

新しいインターフェースは、古いインターフェースのすべての機能を継承し、新機能を追加します。

### 互換性

新しいインターフェースは`QueryInterface`または`ComPtr::As`で取得可能：

```cpp
ComPtr<IDXGIAdapter1> adapter1;
ComPtr<IDXGIAdapter4> adapter4;
// 実行時に変換（対応していない場合は失敗）
HRESULT hr = adapter1.As(&adapter4);
```

---

## DXGIインターフェース

### IDXGIFactory バージョン比較

| インターフェース | 導入 | OS要件 | 主な追加機能 |
|---|---|---|---|
| IDXGIFactory | DXGI 1.0 | Windows Vista SP2+ | 基本的なファクトリ機能 |
| IDXGIFactory1 | DXGI 1.1 | Windows 7+ | アダプタ列挙の改善 |
| IDXGIFactory2 | DXGI 1.2 | Windows 8+ | スワップチェーン作成の改善、フルスクリーン遷移 |
| IDXGIFactory3 | DXGI 1.3 | Windows 8.1+ | スワップチェーンの現在のバックバッファインデックス取得 |
| IDXGIFactory4 | DXGI 1.4 | Windows 10+ | WARP12対応、低レイテンシモード |
| IDXGIFactory5 | DXGI 1.5 | Windows 10 Creators Update | HDR対応チェック、機能サポートクエリ |
| **IDXGIFactory6** | **DXGI 1.6** | **Windows 10 1803+** | **GPUプリファレンスによる列挙 (高性能/省電力)** ⭐ |
| IDXGIFactory7 | DXGI 1.6 | Windows 10 1809+ | GPUアップロード中のアダプタ登録解除検出 |

#### 一次ソース

- [IDXGIFactory interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory)
- [IDXGIFactory6 interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgifactory6)
- [DXGI 1.6 Improvements](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-1-6-improvements)

#### 重要なメソッド (IDXGIFactory6)

```cpp
// GPU選択の優先順位を指定してアダプタを列挙
HRESULT EnumAdapterByGpuPreference(
    UINT Adapter,
    DXGI_GPU_PREFERENCE GpuPreference,  // HIGH_PERFORMANCE / MINIMUM_POWER
    REFIID riid,
    void **ppvAdapter
);
```

---

### IDXGIAdapter バージョン比較

| インターフェース | 導入 | OS要件 | 主な追加機能 |
|---|---|---|---|
| IDXGIAdapter | DXGI 1.0 | Windows Vista SP2+ | 基本的なアダプタ情報（ベンダーID、デバイスID） |
| IDXGIAdapter1 | DXGI 1.1 | Windows 7+ | `DXGI_ADAPTER_DESC1`（より詳細な情報） |
| IDXGIAdapter2 | DXGI 1.2 | Windows 8+ | ステレオ3D対応 |
| IDXGIAdapter3 | DXGI 1.4 | Windows 10+ | GPU仮想アドレスのクエリ、ビデオメモリ予約 |
| **IDXGIAdapter4** | **DXGI 1.6** | **Windows 10 1803+** | **詳細なメモリ情報 (`QueryVideoMemoryInfo`)** ⭐ |

#### 一次ソース

- [IDXGIAdapter1 interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter1)
- [IDXGIAdapter4 interface](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgiadapter4)

#### 重要なメソッド (IDXGIAdapter3/4)

```cpp
// ビデオメモリの詳細情報を取得
HRESULT QueryVideoMemoryInfo(
    UINT NodeIndex,
    DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
    DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo
);
```

#### DXGI_ADAPTER_DESC1 の情報

```cpp
typedef struct DXGI_ADAPTER_DESC1 {
    WCHAR  Description[128];      // アダプタの説明
    UINT   VendorId;              // ベンダーID (NVIDIA: 0x10DE, AMD: 0x1002, Intel: 0x8086)
    UINT   DeviceId;              // デバイスID
    UINT   SubSysId;              // サブシステムID
    UINT   Revision;              // リビジョン
    SIZE_T DedicatedVideoMemory;  // 専用ビデオメモリ
    SIZE_T DedicatedSystemMemory; // 専用システムメモリ
    SIZE_T SharedSystemMemory;    // 共有システムメモリ
    LUID   AdapterLuid;           // アダプタのローカル一意識別子
    UINT   Flags;                 // DXGI_ADAPTER_FLAG
} DXGI_ADAPTER_DESC1;
```

---

## D3D12デバイスインターフェース

### ID3D12Device バージョン比較

| インターフェース | 導入 | OS要件 | 主な追加機能 |
|---|---|---|---|
| ID3D12Device | D3D12 初期 | Windows 10+ | 基本的なデバイス機能 |
| ID3D12Device1 | - | Windows 10 1607+ | パイプラインライブラリ、シェーダー識別子 |
| ID3D12Device2 | - | Windows 10 1703+ | パイプラインステートストリーム |
| ID3D12Device3 | - | Windows 10 1709+ | ヒープシリアル化、仮想アドレス範囲 |
| ID3D12Device4 | - | Windows 10 1803+ | シェーダーモデル6のサポート |
| **ID3D12Device5** | **D3D12** | **Windows 10 1809+** | **レンダーパス、メタコマンド、ステート オブジェクトの作成** ⭐ |
| ID3D12Device6 | - | Windows 10 1903+ | 保護リソースセッション、バックグラウンド処理 |
| ID3D12Device7 | - | Windows 10 2004+ | サンプラーフィードバック、メッシュシェーダー プレビュー |
| ID3D12Device8 | - | Windows 10 20H1+ | D3D12メッシュシェーダー、サンプラーフィードバック正式版 |
| ID3D12Device9 | - | Windows 11+ | シェーダーモデル6.6、強化されたバリア |
| ID3D12Device10 | - | Windows 11 22H2+ | ワークグラフ |

#### 一次ソース

- [ID3D12Device interface](https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device)
- [ID3D12Device5 interface](https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device5)
- [Direct3D 12 Graphics](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-graphics)

#### ID3D12Device5 の主な機能

##### 1. レンダーパス (Render Passes)

タイルベースレンダリング（TBR）の最適化をサポート。メモリ帯域の削減に有効。

```cpp
// レンダーパスの開始
commandList->BeginRenderPass(
    numRenderTargets,
    pRenderTargets,
    pDepthStencil,
    flags
);

// レンダーパスの終了
commandList->EndRenderPass();
```

**一次ソース**: [Render Passes](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-render-passes)

##### 2. メタコマンド (Meta Commands)

ハードウェア固有の最適化された操作（機械学習、レイトレーシングなど）。

```cpp
// メタコマンドの作成
HRESULT CreateMetaCommand(
    REFGUID CommandId,
    UINT NodeMask,
    const void *pCreationParametersData,
    SIZE_T CreationParametersDataSizeInBytes,
    REFIID riid,
    void **ppMetaCommand
);
```

**一次ソース**: [Meta Commands](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-meta-commands)

##### 3. ステート オブジェクト (State Objects)

レイトレーシングパイプラインの構築に使用。

```cpp
HRESULT CreateStateObject(
    const D3D12_STATE_OBJECT_DESC *pDesc,
    REFIID riid,
    void **ppStateObject
);
```

**一次ソース**: [DirectX Raytracing (DXR)](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-raytracing)

---

## Windows バージョンとDirectX対応表

| Windows バージョン | コードネーム | リリース日 | DirectX | DXGI |
|---|---|---|---|---|
| Windows 10 1507 | Threshold 1 | 2015/07 | DirectX 12 初期 | DXGI 1.4 |
| Windows 10 1607 | Anniversary Update | 2016/08 | - | - |
| Windows 10 1703 | Creators Update | 2017/04 | - | DXGI 1.5 |
| Windows 10 1709 | Fall Creators Update | 2017/10 | - | - |
| **Windows 10 1803** | **April 2018 Update** | **2018/04** | - | **DXGI 1.6** |
| **Windows 10 1809** | **October 2018 Update** | **2018/10** | **Device5対応** | - |
| Windows 10 1903 | May 2019 Update | 2019/05 | Device6対応 | - |
| Windows 10 2004 | May 2020 Update | 2020/05 | Device7対応 | - |
| Windows 10 20H1 | - | 2020/05 | Device8対応 | - |
| Windows 11 | - | 2021/10 | Device9対応 | - |
| Windows 11 22H2 | - | 2022/09 | Device10対応 | - |

**一次ソース**: [Windows 10 release information](https://learn.microsoft.com/en-us/windows/release-health/release-information)

---

## 学習用プロジェクトとしての推奨構成

### 推奨インターフェース（2026年現在）

```cpp
// Windows 10 バージョン 1809 (October 2018 Update) 以降を想定
ComPtr<IDXGIFactory6> dxgiFactory;    // GPU選択の改善
ComPtr<IDXGIAdapter4> adapter;        // 詳細なメモリ情報
ComPtr<ID3D12Device5> device;         // レンダーパス、メタコマンド対応
```

### 選択理由

#### ✅ 妥当な最小OS要件
- Windows 10 1809 (2018年リリース) は、2026年現在では十分普及
- 5年以上前のOSバージョンは妥当な最小要件

#### ✅ 学習計画との整合性
本プロジェクトの学習計画（PROJECT_STATUS.md参照）では：
- Phase 3-9: 高度なレンダリング技術の実装
- レンダーパス、PBR、レイトレーシングなどをカバー
- これらの機能はID3D12Device5以降で効率的に実装可能

#### ✅ 書き直しコストの削減
基礎学習段階で古いインターフェースを使用すると：
- 後で高度な機能実装時に書き直しが必要
- インターフェース変更による影響範囲が広い
- 学習効率が低下

#### ✅ 参考資料との互換性
- モダンなDirectX 12教材・サンプルコードと互換性が高い
- GitHubの最新リポジトリとの相性が良い

### 各インターフェースの役割

#### IDXGIFactory6
```cpp
// GPU選択の優先順位指定（高性能GPU優先など）
hr = dxgiFactory->EnumAdapterByGpuPreference(
    0,
    DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
    IID_PPV_ARGS(&adapter)
);
```

**用途**：
- マルチGPU環境での最適なGPU選択
- ノートPCでの内蔵GPU/専用GPU切り替え

#### IDXGIAdapter4
```cpp
// ビデオメモリの使用状況を詳細に取得
DXGI_QUERY_VIDEO_MEMORY_INFO memoryInfo;
adapter->QueryVideoMemoryInfo(
    0,
    DXGI_MEMORY_SEGMENT_GROUP_LOCAL,
    &memoryInfo
);
```

**用途**：
- リソース管理の最適化
- メモリ不足の検出と対処
- パフォーマンス分析

#### ID3D12Device5
```cpp
// レンダーパスを使用した効率的なレンダリング
commandList->BeginRenderPass(
    numRenderTargets,
    renderTargets,
    depthStencil,
    D3D12_RENDER_PASS_FLAG_NONE
);
// レンダリング処理
commandList->EndRenderPass();
```

**用途**：
- タイルベースレンダリングの最適化
- モバイルGPUアーキテクチャとの親和性
- レイトレーシングパイプラインの構築

---

## より古いインターフェースでの実装

### 最小構成（学習初期段階）

基礎学習に集中したい場合は、以下の構成も可能：

```cpp
ComPtr<IDXGIFactory4> dxgiFactory;    // Windows 10 初期対応
ComPtr<IDXGIAdapter1> adapter;        // 基本的なアダプタ情報のみ
ComPtr<ID3D12Device> device;          // 基本的なデバイス機能のみ
```

**メリット**：
- シンプルで理解しやすい
- DirectX 12の基礎に集中できる

**デメリット**：
- Phase 3以降で書き直しが必要
- モダンな最適化手法が使えない

---

## 参考資料

### 公式ドキュメント

- [DirectX Graphics and Gaming](https://learn.microsoft.com/en-us/windows/win32/directx)
- [Direct3D 12 Programming Guide](https://learn.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-guide)
- [DXGI Overview](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi)
- [Feature Levels in Direct3D 12](https://learn.microsoft.com/en-us/windows/win32/direct3d12/hardware-feature-levels)

### インターフェースリファレンス

#### DXGI
- [IDXGIFactory](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory)
- [IDXGIFactory6](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgifactory6)
- [IDXGIAdapter](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter)
- [IDXGIAdapter4](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgiadapter4)

#### D3D12
- [ID3D12Device](https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device)
- [ID3D12Device5](https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device5)

### 仕様書・解説

- [DirectX Specs (GitHub)](https://github.com/microsoft/DirectX-Specs)
- [D3D12 Render Passes Specification](https://microsoft.github.io/DirectX-Specs/d3d/RenderPasses.html)
- [D3D12 Meta Commands Specification](https://microsoft.github.io/DirectX-Specs/d3d/MetaCommands.html)

---

## まとめ

### インターフェース選択の判断基準

| 基準 | 選択 |
|---|---|
| **学習用プロジェクト（本プロジェクト）** | IDXGIFactory6 + IDXGIAdapter4 + ID3D12Device5 ⭐ |
| **基礎学習のみ** | IDXGIFactory4 + IDXGIAdapter1 + ID3D12Device |
| **最新機能の実験** | IDXGIFactory7 + IDXGIAdapter4 + ID3D12Device8-10 |
| **商用プロダクト** | ターゲットOS要件に応じて選択 |

### 本プロジェクトの方針

**現在の構成を維持：**
```cpp
ComPtr<IDXGIFactory7> dxgiFactory;    // ✅ OK（Factory6でも十分）
ComPtr<IDXGIAdapter1> adapter;        // ⚠️ 古いが動作に問題なし
ComPtr<ID3D12Device5> device;         // ✅ 妥当な選択
```

**理由**：
- 動作に問題がない
- 将来的な拡張性を確保
- 学習計画（Phase 1-9）との整合性

---

## 変更履歴

- 2026-01-10: 初版作成
