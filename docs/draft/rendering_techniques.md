# DirectX 12 レンダリング技術項目

---

## 1. DirectX 12 API 基礎

### 1.1 初期化・デバイス管理
- DXGI（DirectX Graphics Infrastructure）
- アダプター列挙、デバイス作成
- スワップチェーン構成
- フェンス同期

### 1.2 コマンドモデル
- コマンドキュー / コマンドアロケータ / コマンドリスト
- バンドル（再利用可能なコマンド群）
- マルチスレッドコマンド記録

### 1.3 リソース管理
- コミットリソース / プレースドリソース / リザーブドリソース
- ヒープタイプ（Default / Upload / Readback）
- リソースバリア / リソースステート遷移
- タイルドリソース

### 1.4 ディスクリプタ管理
- ディスクリプタヒープ（CBV_SRV_UAV / Sampler / RTV / DSV）
- ディスクリプタテーブル
- ルートシグネチャ設計
- ルートパラメータ（定数、ディスクリプタ、テーブル）

### 1.5 パイプラインステートオブジェクト（PSO）
- グラフィックスPSO構成
- 入力レイアウト定義
- ラスタライザステート / ブレンドステート / 深度ステンシルステート
- コンピュートPSO

---

## 2. GPUパイプライン理論

### 2.1 グラフィックスパイプライン
- 入力アセンブラ（IA）
- 頂点シェーダー（VS）
- ハルシェーダー（HS）/ テッセレータ / ドメインシェーダー（DS）
- ジオメトリシェーダー（GS）
- ストリームアウトプット（SO）
- ラスタライザ（RS）
- ピクセルシェーダー（PS）
- 出力マージャー（OM）

### 2.2 コンピュートパイプライン
- コンピュートシェーダー（CS）
- スレッドグループ / ディスパッチ
- 共有メモリ（groupshared）
- 同期（GroupMemoryBarrier など）

### 2.3 メモリアーキテクチャ
- GPU メモリ階層
- キャッシュコヒーレンシ
- メモリ帯域とレイテンシ

---

## 3. HLSL シェーダープログラミング

### 3.1 基礎文法
- データ型（スカラー、ベクトル、行列）
- セマンティクス（SV_Position、SV_Target など）
- 組み込み関数（数学、テクスチャサンプリング）

### 3.2 リソースバインディング
- 定数バッファ（cbuffer）
- 構造化バッファ（StructuredBuffer）
- テクスチャ（Texture2D、TextureCube など）
- サンプラーステート
- UAV（RWTexture、RWBuffer）

### 3.3 Shader Model 6.x 機能
- Wave Intrinsics（SM 6.0+）
- メッシュシェーダー / アンプリフィケーションシェーダー（SM 6.5+）
- レイトレーシングシェーダー（SM 6.3+）
- サンプラーフィードバック（SM 6.5+）
- Work Graphs（SM 6.8+）

---

## 4. レンダリングアーキテクチャ

### 4.1 フォワードレンダリング
- シングルパス実装
- マルチライト処理の課題
- Zプリパス最適化

### 4.2 ディファードレンダリング
- G-Buffer設計（アルベド、法線、深度、ラフネス/メタリックなど）
- ライティングパス
- 帯域幅の考慮
- 透明オブジェクトの扱い

### 4.3 タイルベース / クラスタベース
- Forward+（Tiled Forward）
- Clustered Shading
- ライトカリング（コンピュートシェーダー）

### 4.4 Visibility Buffer（Deferred Texturing）
- 三角形ID + バリセントリック座標
- マテリアルフェッチの遅延
- 帯域幅削減

---

## 5. ライティング

### 5.1 ライティングモデル基礎
- Lambert 拡散反射
- Blinn-Phong 鏡面反射
- エネルギー保存の概念

### 5.2 ライト種別の実装
- Directional Light
- Point Light（減衰関数）
- Spot Light（コーン計算）
- Area Light（LTC: Linearly Transformed Cosines）

### 5.3 イメージベースドライティング（IBL）
- 環境マップ（Cubemap）生成
- プリフィルタード環境マップ
- BRDF積分LUT
- 球面調和関数（SH）ライティング

---

## 6. PBR（物理ベースレンダリング）

### 6.1 理論基礎
- レンダリング方程式
- BRDF の定義と性質
- エネルギー保存
- フレネル効果（Schlick 近似）

### 6.2 マイクロファセット理論
- 法線分布関数（NDF）：GGX / Beckmann / Blinn
- 幾何減衰関数（G）：Smith / Schlick-GGX
- Cook-Torrance BRDF

### 6.3 ワークフロー
- Metallic-Roughness
- Specular-Glossiness
- Disney Principled BRDF

### 6.4 高度なマテリアル
- クリアコート（多層BRDF）
- 異方性反射（Anisotropic GGX）
- シーン / ファブリック
- 薄膜干渉

---

## 7. サブサーフェススキャタリング（SSS）

### 7.1 理論
- BSSRDF
- ディフュージョンプロファイル

### 7.2 実装手法
- Texture-Space Diffusion
- Screen-Space SSS（Separable SSS）
- Pre-Integrated Skin Shading
- Random Walk SSS（パストレーシング）

---

## 8. シャドウ技術

### 8.1 基本シャドウマッピング
- 深度マップ生成
- 射影テクスチャマッピング
- シャドウバイアス（定数 / スロープスケール / ノーマルオフセット）

### 8.2 高品質フィルタリング
- PCF（Percentage Closer Filtering）
- Poisson Disk Sampling
- PCSS（Percentage Closer Soft Shadows）
- VSM / ESM / MSM

### 8.3 大規模シーン対応
- カスケードシャドウマップ（CSM）
- Sample Distribution Shadow Maps（SDSM）
- Virtual Shadow Maps

### 8.4 SDF シャドウ
#### 8.4.1 SDF 基礎
- Signed Distance Field の概念
- 3D SDF テクスチャ生成（オフライン / ランタイム）
- SDF のメモリ・解像度トレードオフ

#### 8.4.2 レイマーチングによるシャドウ
- Sphere Tracing アルゴリズム
- ソフトシャドウ係数の計算（最小距離 / 距離比）
- ステップ数と精度のバランス

#### 8.4.3 実装技法
- オブジェクトごとの SDF vs グローバル SDF
- SDF の合成（Union / Intersection / Subtraction）
- 動的オブジェクトへの対応
- カスケード SDF / マルチスケール SDF

#### 8.4.4 応用
- SDF ベースアンビエントオクルージョン
- SDF ベースグローバルイルミネーション
- SDF とメッシュシャドウのハイブリッド

### 8.5 特殊シャドウ
- コンタクトシャドウ（スクリーンスペースレイマーチ）
- レイトレースシャドウ

---

## 9. グローバルイルミネーション

### 9.1 アンビエントオクルージョン
- SSAO（Screen Space Ambient Occlusion）
- HBAO（Horizon-Based AO）
- GTAO（Ground Truth AO）
- レイトレース AO

### 9.2 間接照明の近似
- SSGI（Screen Space GI）
- Light Propagation Volumes（LPV）
- Voxel Cone Tracing（VXGI）
- Radiance Cascades

### 9.3 プローブベース
- Irradiance Probes
- Irradiance Volumes
- DDGI（Dynamic Diffuse GI）

### 9.4 レイトレーシングGI
- パストレーシング基礎
- ReSTIR（Reservoir-based Spatiotemporal Importance Resampling）
- デノイジング（SVGF、A-SVGF）

---

## 10. 反射技術

### 10.1 環境マップ反射
- キューブマップ反射
- パララックス補正キューブマップ
- プローブブレンディング

### 10.2 スクリーンスペース反射（SSR）
- リニアレイマーチ
- Hi-Z トレーシング
- 時間的フィルタリング

### 10.3 レイトレース反射
- 反射レイ生成
- 多重バウンス
- ラフネスに応じたレイ分散

---

## 11. ポストプロセッシング

### 11.1 HDR パイプライン
- HDR レンダーターゲット（R16G16B16A16_FLOAT など）
- 露出制御（自動露出 / ヒストグラム）
- トーンマッピング（Reinhard / ACES / Uncharted 2 / AgX）

### 11.2 ブルーム
- 輝度抽出（閾値）
- ダウンサンプル / アップサンプルチェーン
- ガウスブラー / カワセブラー

### 11.3 被写界深度（DoF）
- Circle of Confusion 計算
- ガウスブラー DoF
- ボケシミュレーション（スプライトベース / ギャザーベース）

### 11.4 モーションブラー
- カメラモーションブラー
- オブジェクトモーションブラー（Velocity Buffer）
- タイルベースモーションブラー

### 11.5 アンチエイリアシング
- MSAA（マルチサンプル）
- FXAA（Fast Approximate AA）
- SMAA（Subpixel Morphological AA）
- TAA（Temporal AA）

### 11.6 その他
- 色収差
- ビネット
- フィルムグレイン
- レンズフレア

---

## 12. ボリュームレンダリング

### 12.1 フォグ
- 均一フォグ / 指数フォグ
- ハイトフォグ

### 12.2 ボリューメトリックライティング
- レイマーチング
- Froxel（Frustum-Voxel）
- Epipolar Sampling

### 12.3 雲
- ボリュメトリッククラウド
- ノイズベースモデリング（Worley / Perlin）
- 光散乱近似

---

## 13. レイトレーシング / パストレーシング

### 13.1 DXR（DirectX Raytracing）基礎
- Acceleration Structure（BLAS / TLAS）
- シェーダーテーブル構成
- レイ生成 / 最近接ヒット / ミス / Any-Hit シェーダー

### 13.2 BVH構築
- SAH（Surface Area Heuristic）
- リフィット vs リビルド
- BLAS圧縮

### 13.3 ハイブリッドレンダリング
- ラスタ + RT反射
- ラスタ + RTシャドウ
- ラスタ + RT AO

### 13.4 フルパストレーシング
- モンテカルロ積分
- 重点サンプリング
- MIS（Multiple Importance Sampling）
- ロシアンルーレット

### 13.5 デノイジング
- 時間的蓄積
- SVGF
- NRD（NVIDIA Real-time Denoisers）のアルゴリズム理解

---

## 14. NPR（ノンフォトリアリスティック）

### 14.1 トゥーンシェーディング
- 離散化ランプ
- ハーフトーン

### 14.2 アウトライン
- 背面法（法線押し出し）
- ポストプロセスエッジ検出（Sobel / Roberts / Laplacian）
- 深度・法線不連続検出

### 14.3 スタイライズド表現
- ハッチング
- 水彩 / 油絵風
- ピクセルアート風

---

## 15. 透明・半透明レンダリング

### 15.1 基本
- アルファブレンディング
- アルファテスト（カットアウト）
- 描画順序とソート

### 15.2 Order Independent Transparency（OIT）
- Depth Peeling
- Per-Pixel Linked Lists
- Weighted Blended OIT
- Moment-Based OIT

---

## 16. 高度なジオメトリ技術

### 16.1 テッセレーション
- Hull / Domain シェーダー
- 適応テッセレーション
- ディスプレイスメントマッピング

### 16.2 メッシュシェーダー
- Amplification + Mesh シェーダーモデル
- Meshlet 分割
- カリング（コーン / フラスタム / オクルージョン）

### 16.3 プロシージャルジオメトリ
- コンピュートシェーダーによる頂点生成
- Indirect Drawing

---

## 17. テクスチャ技術

### 17.1 基礎
- ミップマップ生成
- フィルタリング（Bilinear / Trilinear / Anisotropic）
- テクスチャアドレッシング

### 17.2 圧縮フォーマット
- BC1-BC7（Block Compression）
- 各フォーマットの特性と用途

### 17.3 高度技法
- パララックスマッピング
- パララックスオクルージョンマッピング（POM）
- リリーフマッピング
- Virtual Texturing（Megatexture）
- Bindless Textures

---

## 18. プロファイリング・デバッグ

### 18.1 プロファイリングツール
- PIX for Windows
- RenderDoc
- NVIDIA Nsight Graphics
- AMD Radeon GPU Profiler

### 18.2 GPU タイミング計測
- タイムスタンプクエリ（ID3D12QueryHeap）
- パイプライン統計クエリ
- GPU タイミングの可視化

### 18.3 パフォーマンス分析
- ボトルネック特定（CPU / GPU バウンド）
- シェーダー占有率（Occupancy）
- メモリ帯域使用量
- ドローコール分析
- オーバードロー検出

### 18.4 クラッシュ調査
#### 18.4.1 デバッグレイヤー
- D3D12 Debug Layer 有効化
- GPU-Based Validation（GBV）
- DRED（Device Removed Extended Data）

#### 18.4.2 よくあるクラッシュ原因
- リソースバリア不正
- ディスクリプタヒープ溢れ
- ルートシグネチャ不一致
- 同期エラー（フェンス待機漏れ）
- 解放済みリソースへのアクセス

#### 18.4.3 デバッグ手法
- PIX GPU キャプチャ解析
- シェーダーデバッグ（PIX シェーダーデバッガ）
- メモリリーク検出
- Aftermath（NVIDIA）による事後解析

### 18.5 検証とテスト
- 異なる GPU ベンダーでのテスト
- 異なる Feature Level でのテスト
- ストレステスト
- 自動化テスト

---

## 19. 最適化技術

### 19.1 カリング
- フラスタムカリング
- オクルージョンカリング（Hi-Z、HZB Occlusion Culling）
- GPU駆動カリング

### 19.2 LOD
- 離散LOD
- 連続LOD
- Nanite風仮想ジオメトリの概念

### 19.3 描画効率化
- Indirect Rendering（ExecuteIndirect）
- Multi-Draw Indirect
- Bindless Resources

### 19.4 並列化
- 非同期コンピュート
- マルチキュー活用
- フレームグラフ / レンダーグラフ

### 19.5 プロファイリング連携
- ボトルネック特定後の最適化フロー
- イテレーティブな改善プロセス

---

## 推奨リソース

- **Microsoft DirectX 12 公式サンプル**（GitHub: microsoft/DirectX-Graphics-Samples）
- **PIX for Windows**（プロファイリング）
- **GPU Gems / GPU Pro / GPU Zen シリーズ**
- **Real-Time Rendering 4th Edition**
- **Physically Based Rendering: From Theory to Implementation（PBRT）**
