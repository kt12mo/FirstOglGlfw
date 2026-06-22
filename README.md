[README.md](https://github.com/user-attachments/files/29186536/README.md)
# Billiards Physics Simulator (FirstOglGlfw)

C++ と OpenGL / GLFW を用いて開発した、リアルタイム3Dビリヤード物理シミュレーターです。
球体の3D描画から、ボール間の衝突判定・物理演算までを自ら設計・実装しました。

## 動作の様子

<img width="319" alt="break shot" src="https://github.com/user-attachments/assets/4f1f7475-b075-4610-9382-41db16867f23" />
<img width="314" alt="ball collision" src="https://github.com/user-attachments/assets/5dc5bdb6-10b2-40bf-86cf-60a64671bfe3" />
<img width="316" alt="15-ball rack" src="https://github.com/user-attachments/assets/fbc74ab1-a6b2-4fc6-a190-86ad4929be30" />

## 概要

ビリヤードのブレイクショットや球同士の衝突を、物理法則に基づいてリアルタイムに
シミュレーションします。OpenGL の固定機能パイプラインで3D描画を行い、GLFW で
ウィンドウ生成・ユーザー入力を管理しています。

## 主な機能

- 球体のリアルタイム3D描画（`GL_QUAD_STRIP` による塗りつぶし球面）
- ボール間の衝突判定と、衝突時の速度ベクトル分解（内積を用いた運動量のやり取り）
- 球の重なり補正による、めり込みの解消
- 公式カラーに準じた15ボールのラック配置
- カメラ視点の制御

## 使用技術

| 分類 | 技術 |
|------|------|
| 言語 | C++ |
| グラフィックス | OpenGL |
| ウィンドウ・入力管理 | GLFW |

## 設計

- `Ball` クラス：各ボールの位置・速度・色などの状態と、更新処理を管理
- `Table` クラス：テーブルの描画と、クッション・ポケットなどの境界処理を管理
- シングルトンパターンを用いて、全体で共有する状態を一元管理

## ビルド・実行方法

```bash
# 例（環境に合わせて調整してください）
g++ main.cpp -o billiards -lGL -lglfw -lGLU
./billiards
```

## 操作方法

- マウス：視点の操作

## 今後の課題

- ポケットイン判定とゲームルールの実装
- 物理パラメータの調整による挙動の自然さ向上

---

開発：（[@kt12mo](https://github.com/kt12mo)）
