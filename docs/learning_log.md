# Learning Log

## エントリー

<!-- 以下に自動的にエントリーが追加されます -->

### 2026-01-07 01:08 - 学習
DXGIは、ハードウェアレベルの低レイヤとの懸け橋になる。interfaceとなることでハードウェアの差を吸収できる

**🤖 AI補足 (01:09):**
DXGIはDirect3D 10/11/12で共通して使われる低レベルAPIです。グラフィックスアダプタの列挙、スワップチェーン管理、フルスクリーン遷移など、ハードウェア固有の処理を抽象化し、Direct3Dランタイムから独立して動作します。

> 📚 参照:
> [DXGI Overview - Microsoft Learn](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi), [Programming Guide for DXGI - Microsoft Learn](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dx-graphics-dxgi-overviews)

### 2026-01-07 01:19 - 学習
Adapter: GPU1つに対してあるようなもの、ほぼGPUドライバに近い。EnumAdapter1はGPUが今使われているかに関係なくあるものを列挙して、EnumAdapterは使われているものだけを列挙する

**🤖 AI補足 (01:19):**
IDXGIAdapter1は物理的なグラフィックスアダプタ（GPU）を表すインターフェースです。EnumAdapters1()は、モニター出力の有無に関わらずシステム内の全アダプタを列挙します（DXGI 1.1以降）。一方、EnumAdapters()は出力が接続されているアダプタのみを列挙するため、ヘッドレスGPUは検出されません。

> 📚 参照:
> [IDXGIFactory1::EnumAdapters1 - Microsoft Learn](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgifactory1-enumadapters1), [IDXGIAdapter1 Interface - Microsoft Learn](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter1)
