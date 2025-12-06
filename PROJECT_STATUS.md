# RenderingSandbox - プロジェクト状況と学習計画

最終更新: 2025-12-06

---

## 📋 プロジェクト概要

**RenderingSandbox** は、DirectX 12を使用したレンダリング技術の学習と実験を目的としたC++20プロジェクトです。

### 基本情報
- **言語**: C++20
- **プラットフォーム**: Windows 10+
- **開発環境**: Visual Studio 2022
- **ツールセット**: v145
- **プロジェクトタイプ**: Win32コンソールアプリケーション

### 参考資料
- **書籍**: [DirectX12 Mastery Vol.1](https://techbookfest.org/product/v0Zc7hA6EwnBz9YYMqbxP6)
- **参考リポジトリ**: [book-directx12-mastery_1](https://github.com/techmadot/book-directx12-mastery_1)

---

## 📂 現在のリポジトリ構造

```
RenderingSandbox/
├── .claude/                          # Claude Code設定
│   ├── agents/
│   │   └── zenn-doc-writer.md
│   └── settings.local.json
├── .vs/                              # Visual Studio設定（自動生成）
├── Documents/                        # 学習ドキュメント
│   ├── learning_phases.md            # 学習フェーズ詳細（Phase 1-9）
│   ├── rendering_techniques.md       # DirectX 12技術項目カタログ
│   └── [今後追加予定]
├── RenderingSandbox/                 # メインプロジェクト
│   ├── RenderingSandbox.vcxproj      # プロジェクトファイル
│   ├── RenderingSandbox.vcxproj.filters
│   └── RenderingSandbox.vcxproj.user
├── CLAUDE.md                         # Claude Code用プロジェクトガイド
├── PROJECT_STATUS.md                 # 本ファイル（進捗管理）
└── RenderingSandbox.slnx             # ソリューションファイル
```

### 今後追加予定のディレクトリ構造

参考リポジトリに基づき、以下の構造を構築予定：

```
RenderingSandbox/
├── Common/                           # 共通ライブラリ（計画中）
│   ├── Include/                      # ヘッダーファイル
│   ├── Src/                          # 共通実装
│   └── External/                     # 外部ライブラリ
│       ├── imgui/                    # Dear ImGui 1.91.0
│       ├── assimp/                   # Assimp 5.3.1
│       └── stb/                      # stb_image, stb_image_resize
├── HelloTriangle/                    # Stage 1（計画中）
│   ├── Shaders/                      # HLSLシェーダー
│   ├── Main.cpp
│   └── [その他実装ファイル]
├── DrawModel/                        # Stage 2（計画中）
├── ComputeShader/                    # Stage 3（計画中）
├── Tessellation/                     # Stage 3（計画中）
└── [その他のサンプル]
```

---

## 🎯 学習計画の全体像

### 短期計画（参考リポジトリベース）

参考リポジトリの構造に基づく3段階の学習：

#### **Stage 1: HelloTriangle（基礎）** ← 現在ここ
**目標**: DirectX 12の基本的な初期化とシンプルな三角形の描画

**学習項目**:
- DirectX 12デバイスの初期化
- スワップチェーンの作成
- コマンドキュー、コマンドリスト、コマンドアロケーターの理解
- 基本的なパイプラインステートオブジェクト（PSO）
- 頂点バッファとシェーダー（Vertex/Pixel）の基礎
- シンプルな三角形のレンダリング

**実装計画**:
1. Windowクラスの作成（Win32 APIウィンドウ管理）
2. DirectX 12デバイスと基本リソースの初期化
3. レンダリングパイプラインのセットアップ
4. 基本的なHLSLシェーダーの作成
5. 三角形の描画ループ実装

**対応する技術項目**（`rendering_techniques.md`参照）:
- 1.1 初期化・デバイス管理
- 1.2 コマンドモデル
- 1.3 リソース管理（基礎）
- 1.4 ディスクリプタ管理（基礎）
- 1.5 パイプラインステートオブジェクト
- 3.1 HLSL基礎文法

---

#### **Stage 2: DrawModel（モデル描画）**
**目標**: 3Dモデルの読み込みと描画

**学習項目**:
- モデルローダーの実装（Assimp統合）
- テクスチャマッピング
- トランスフォーム（移動・回転・拡大縮小）
- カメラシステムの実装
- ライティングの基礎

**対応する技術項目**:
- 3.2 リソースバインディング
- 5.1 ライティングモデル基礎
- 17.1 テクスチャ基礎

---

#### **Stage 3: 高度な技術**
**目標**: より高度なレンダリング技術の習得

**学習項目**:
- コンピュートシェーダー
- テッセレーション
- ジオメトリシェーダー
- マルチパスレンダリング

**対応する技術項目**:
- 2.2 コンピュートパイプライン
- 16.1 テッセレーション
- 2.1 グラフィックスパイプライン（GS）

---

### 長期計画（22ヶ月以上）

詳細な9フェーズの学習計画については、[`Documents/learning_phases.md`](./Documents/learning_phases.md)を参照してください。

#### フェーズ一覧

| Phase | テーマ | 期間 | 主要技術 |
|-------|--------|------|----------|
| **Phase 1** | DirectX 12 基盤構築 | 2-3ヶ月 | 初期化、三角形描画、テクスチャ、深度バッファ |
| **Phase 2** | 基本レンダリング | 2-3ヶ月 | モデルローダー、カメラ、ライティング、シャドウマッピング |
| **Phase 3** | プロファイリング・デバッグ | 1-2ヶ月 | PIX、デバッグレイヤー、GPU計測 |
| **Phase 4** | PBR パイプライン | 2-3ヶ月 | PBR理論、IBL、HDR、トーンマッピング |
| **Phase 5** | ディファードレンダリング | 2ヶ月 | G-Buffer、SSAO、マルチライト |
| **Phase 6** | 高品質シャドウ・反射 | 2-3ヶ月 | CSM、PCF/PCSS、SSR、TAA |
| **Phase 7** | コンピュートシェーダー活用 | 2ヶ月 | GPUパーティクル、ライトカリング、GPUカリング |
| **Phase 8** | レイトレーシング | 3ヶ月 | DXR、RTシャドウ/反射/AO |
| **Phase 9** | 先端技術 | 継続的 | メッシュシェーダー、パストレーシング、レンダーグラフ |

**全技術項目の詳細**: [`Documents/rendering_techniques.md`](./Documents/rendering_techniques.md)

---

## ✅ 現在の進捗状況

### 完了項目
- [x] プロジェクト基本構造の作成
- [x] Visual Studio環境の構築
- [x] 学習資料の整理（learning_phases.md, rendering_techniques.md）
- [x] プロジェクト管理ドキュメントの作成（本ファイル）

### 進行中
- [ ] **Stage 1: HelloTriangle実装準備** ← 現在の焦点

### 未着手
- [ ] 共通ライブラリの準備（Common フォルダ構造）
- [ ] 外部ライブラリのセットアップ（Dear ImGui, Assimp, stb）
- [ ] Stage 2: DrawModel実装
- [ ] Stage 3: 高度な技術の実装

---

## 🚀 次のステップ（優先順位順）

### 1. プロジェクト構造の整備（推奨）
参考リポジトリに倣い、以下のディレクトリ構造を作成：
```
Common/
  ├── Include/
  ├── Src/
  └── External/
HelloTriangle/
  ├── Shaders/
  └── [ソースファイル]
```

### 2. 外部ライブラリのセットアップ
必要なライブラリ：
- **Dear ImGui** 1.91.0（デバッグUI用）
- **Assimp** 5.3.1（3Dモデル読み込み - Stage 2以降で使用）
- **stb_image**（画像ローディング）

### 3. HelloTriangle実装開始
以下の順序で実装：
1. Win32ウィンドウの作成
2. DirectX 12の初期化（デバイス、コマンドキュー、スワップチェーン）
3. ルートシグネチャとパイプラインステートの作成
4. 頂点バッファの作成
5. HLSLシェーダーの作成（Vertex Shader, Pixel Shader）
6. レンダリングループの実装

---

## 📚 参考リポジトリとの対応関係

### 参考リポジトリの構造
```
book-directx12-mastery_1/
├── Common/                    # 共通コンポーネント
├── HelloTriangle/             # 基本サンプル（Stage 1相当）
├── DrawModel/                 # モデル描画（Stage 2相当）
├── ComputeShader/             # コンピュートシェーダー（Stage 3）
└── Tessellation/              # テッセレーション（Stage 3）
```

### 学習の進め方
1. **参考リポジトリのコードを読む**（理解）
2. **自分で実装する**（実践）
3. **動作確認とデバッグ**（検証）
4. **技術項目ドキュメントで理論を深める**（定着）

---

## 🛠️ ビルドと実行

### ビルド方法
- **Visual Studioでのビルド**: `F7`キーまたはビルドメニューから「ソリューションのビルド」
- **コマンドライン**:
  ```bash
  msbuild RenderingSandbox.slnx -p:Configuration=Debug -p:Platform=x64
  msbuild RenderingSandbox.slnx -p:Configuration=Release -p:Platform=x64
  ```

### 推奨構成
- **プラットフォーム**: x64
- **開発時**: Debug
- **最終ビルド**: Release

### 実行方法
```bash
# Debug build
RenderingSandbox\x64\Debug\RenderingSandbox.exe

# Release build
RenderingSandbox\x64\Release\RenderingSandbox.exe
```

---

## 📖 ドキュメント一覧

| ファイル | 内容 |
|---------|------|
| `PROJECT_STATUS.md` | 本ファイル - プロジェクト全体の進捗と計画 |
| `CLAUDE.md` | Claude Code用のプロジェクトガイド |
| `Documents/learning_phases.md` | 詳細な9フェーズ学習計画（22ヶ月） |
| `Documents/rendering_techniques.md` | DirectX 12技術項目の完全カタログ |

---

## 📝 メモ・注意事項

### 重要な学習方針
1. **Phase 3（プロファイリング・デバッグ）は早期習得を推奨**
   - 問題発生時の調査時間を大幅に短縮
   - 以降すべてのフェーズで活用される基盤スキル

2. **並行学習推奨項目**
   - 線形代数、三角関数（数学基礎）
   - GPUアーキテクチャの理解
   - SIGGRAPH / GDC の論文・資料

3. **参考リポジトリの活用**
   - 書籍と若干の差異がある可能性（不具合修正等）
   - Visual Studio 2022での動作確認済み
   - CMakeが必要（PrepareAssimp.bat実行時）

### 開発環境の注意点
- プラットフォームツールセット: 現在v145、v143（VS2022推奨）へのアップデート検討
- C++20機能を積極的に活用
- デバッグビルドではSDLチェックが有効

---

## 🔗 関連リンク

- [DirectX12 Mastery Vol.1（書籍）](https://techbookfest.org/product/v0Zc7hA6EwnBz9YYMqbxP6)
- [参考リポジトリ](https://github.com/techmadot/book-directx12-mastery_1)
- [Microsoft DirectX 12 公式サンプル](https://github.com/microsoft/DirectX-Graphics-Samples)
- [Microsoft DirectX ドキュメント](https://learn.microsoft.com/windows/win32/direct3d12/direct3d-12-graphics)

---

**更新履歴**:
- 2025-12-06: 初版作成、プロジェクト構造と学習計画の整理
