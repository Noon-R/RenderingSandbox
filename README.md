# RenderingSandbox

DirectX 12を使用したレンダリング技術の学習と実験用プロジェクト

## 📖 プロジェクトについて

このプロジェクトは、[DirectX12 Mastery Vol.1](https://techbookfest.org/product/v0Zc7hA6EwnBz9YYMqbxP6)の書籍と[参考リポジトリ](https://github.com/techmadot/book-directx12-mastery_1)を基に、DirectX 12のレンダリング技術を段階的に学習することを目的としています。

## 🚀 クイックスタート

### 必要な環境
- Windows 10以上
- Visual Studio 2022
- C++20サポート

### ビルド方法
```bash
# Visual Studioで開く
RenderingSandbox.slnx

# またはコマンドラインから
msbuild RenderingSandbox.slnx -p:Configuration=Debug -p:Platform=x64
```

## 📚 ドキュメント

- **[PROJECT_STATUS.md](./PROJECT_STATUS.md)** - プロジェクト全体の進捗状況と詳細な学習計画
- **[CLAUDE.md](./CLAUDE.md)** - プロジェクトの技術的なガイドライン
- **[学習フェーズ詳細](./Documents/learning_phases.md)** - 9フェーズの詳細な学習計画（22ヶ月）
- **[レンダリング技術項目](./Documents/rendering_techniques.md)** - DirectX 12技術の完全カタログ

## 🎯 学習ステージ

### Stage 1: HelloTriangle（現在）
DirectX 12の基礎 - デバイス初期化、シンプルな三角形の描画

### Stage 2: DrawModel
3Dモデルの読み込みと描画、ライティング基礎

### Stage 3: 高度な技術
コンピュートシェーダー、テッセレーション、ジオメトリシェーダー

詳細は [PROJECT_STATUS.md](./PROJECT_STATUS.md) を参照してください。

## 📖 参考資料

- [DirectX12 Mastery Vol.1（書籍）](https://techbookfest.org/product/v0Zc7hA6EwnBz9YYMqbxP6)
- [参考リポジトリ](https://github.com/techmadot/book-directx12-mastery_1)
- [Microsoft DirectX 12 公式ドキュメント](https://learn.microsoft.com/windows/win32/direct3d12/direct3d-12-graphics)

## 📝 ライセンス

学習・研究目的のプロジェクトです。
