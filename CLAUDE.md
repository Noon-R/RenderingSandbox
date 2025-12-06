# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

RenderingSandboxは、C++20を使用したWindowsベースのレンダリング実験・学習用プロジェクトです。Visual Studio 2019/2022でのビルドを想定しており、グラフィックス技術の実装とテストを目的としています。

## 📚 重要なドキュメント

プロジェクトの詳細情報は以下のドキュメントを参照してください：

- **[PROJECT_STATUS.md](./PROJECT_STATUS.md)** - **必読**: プロジェクト全体の進捗状況、学習計画、リポジトリ構造
- **[Documents/learning_phases.md](./Documents/learning_phases.md)** - 9フェーズの詳細な学習計画（Phase 1-9, 22ヶ月）
- **[Documents/rendering_techniques.md](./Documents/rendering_techniques.md)** - DirectX 12技術項目の完全カタログ（セクション1-19）

## Build and Development Commands

### Building the Project
- **Visual Studioでのビルド**: F7キーまたはビルドメニューから「ソリューションのビルド」
- **コマンドライン（MSBuild）**:
  ```
  msbuild RenderingSandbox.slnx -p:Configuration=Debug -p:Platform=x64
  msbuild RenderingSandbox.slnx -p:Configuration=Release -p:Platform=x64
  ```

### Available Configurations
- **Platforms**: x86, x64
- **Configurations**: Debug, Release
- **推奨**: x64 Debugで開発、x64 Releaseで最終ビルド

### Running the Application
```
# Debug build
RenderingSandbox\x64\Debug\RenderingSandbox.exe

# Release build  
RenderingSandbox\x64\Release\RenderingSandbox.exe
```

## Project Architecture

### Technology Stack
- **言語**: C++20
- **プラットフォーム**: Windows 10+
- **ツールセット**: v143 (Visual Studio 2022)
- **文字セット**: Unicode
- **プロジェクトタイプ**: Win32コンソールアプリケーション

### Project Structure
```
RenderingSandbox/
├── RenderingSandbox.slnx          # ソリューションファイル
└── RenderingSandbox/              # メインプロジェクト
    ├── RenderingSandbox.vcxproj   # プロジェクトファイル
    ├── RenderingSandbox.vcxproj.filters
    └── RenderingSandbox.vcxproj.user
```

### Development Notes
- C++20機能を積極的に活用（modules, concepts, ranges等）
- レンダリング関連のコードは適切に分離・モジュール化
- Windows APIまたはDirectX/OpenGLの統合を想定
- デバッグビルドではSDLチェックが有効

### Coding Standards
- **警告レベル**: Level3（厳格）
- **コンフォーマンスモード**: 有効
- **SDLチェック**: 有効
- **最適化**: リリースビルドで関数レベルリンクと組み込み関数を使用

## Learning Path - DirectX 12 Mastery

### 参考資料
- **書籍**: [DirectX12 Mastery Vol.1](https://techbookfest.org/product/v0Zc7hA6EwnBz9YYMqbxP6)
- **リポジトリ**: [book-directx12-mastery_1](https://github.com/techmadot/book-directx12-mastery_1)

### 学習ステージ

#### Stage 1: 基礎 - HelloTriangle
**目標**: DirectX 12の基本的な初期化とシンプルな三角形の描画
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

#### Stage 2: モデル描画 - DrawModel
**目標**: 3Dモデルの読み込みと描画
- モデルローダーの実装（Assimp統合）
- テクスチャマッピング
- トランスフォーム（移動・回転・拡大縮小）
- カメラシステムの実装
- ライティングの基礎

#### Stage 3: 高度な技術
**目標**: より高度なレンダリング技術の習得
- コンピュートシェーダー
- テッセレーション
- ジオメトリシェーダー
- マルチパスレンダリング

### 必要なライブラリとツール
- **Dear ImGui**: 1.91.0（デバッグUI用）
- **Assimp**: 5.3.1（3Dモデル読み込み）
- **stb_image**: シングルヘッダー画像ローディング
- **CMake**: ビルドシステム（一部ライブラリで使用）

### 現在の進捗
- [x] プロジェクト基本構造の作成
- [ ] Stage 1: HelloTriangle実装準備
- [ ] Stage 2: DrawModel実装
- [ ] Stage 3: 高度な技術の実装

### 次のステップ
1. 共通ライブラリの準備（Common フォルダ構造）
2. HelloTriangle実装開始
3. 基本的なウィンドウシステムとDirectX 12初期化コード