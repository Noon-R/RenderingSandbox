# RenderingSandbox - Zenn コンテンツ

このディレクトリには、RenderingSandboxプロジェクトのZenn投稿用コンテンツが含まれています。

## 📁 ディレクトリ構成

```
docs/zenn/
├── articles/          # Zenn記事
├── books/            # Zenn本
├── images/           # 画像ファイル
├── package.json      # Zenn CLI設定
├── .gitignore        # Git除外設定
└── README.md         # このファイル
```

## 🚀 セットアップ

### 1. Zenn CLIのインストール

```bash
cd docs/zenn
npm install
```

### 2. プレビューサーバーの起動

```bash
npm run preview
```

ブラウザで `http://localhost:8000` にアクセスして、記事をプレビューできます。

## ✍️ 記事の作成

### 新しい記事を作成

```bash
npm run new:article
```

記事ファイルが `articles/` ディレクトリに作成されます。

### 新しい本を作成

```bash
npm run new:book
```

本のディレクトリが `books/` 以下に作成されます。

## 📝 記事のフロントマター

記事の先頭には以下のようなフロントマターを記述します：

```yaml
---
title: "記事タイトル"
emoji: "🎨"
type: "tech"  # tech: 技術記事 / idea: アイデア記事
topics: ["directx12", "cpp", "graphics", "rendering"]
published: false  # 公開設定（true: 公開 / false: 下書き）
---
```

## 🎯 投稿予定のコンテンツ

### 記事候補

- DirectX 12入門：HelloTriangleの実装
- DirectX 12のリソース管理とディスクリプタヒープ
- コマンドリストとコマンドアロケーターの理解
- PBRパイプラインの実装
- ディファードレンダリングの実装

### 本候補

- DirectX 12によるレンダリング技術の実装ガイド
- グラフィックスプログラミング学習ロードマップ

## 📚 参考リンク

- [Zenn公式ドキュメント](https://zenn.dev/zenn/articles/zenn-cli-guide)
- [Zenn CLIで記事・本を管理する方法](https://zenn.dev/zenn/articles/zenn-cli-guide)
- [Markdown記法チートシート](https://zenn.dev/zenn/articles/markdown-guide)

## 📌 注意事項

- 記事はすべてMarkdown形式で記述します
- 画像は `images/` ディレクトリに配置し、相対パスで参照します
- 記事のファイル名は公開後に変更できません
- `published: true` にすると一般公開されます（下書きの場合は `false`）

## 🔄 Gitとの連携

Zennはリポジトリと連携して記事を管理できます：

1. GitHubリポジトリと連携
2. `docs/zenn/` ディレクトリをZennと同期
3. プッシュすると自動的にZennに反映

詳細は[Zenn CLIの導入ガイド](https://zenn.dev/zenn/articles/install-zenn-cli)を参照してください。
