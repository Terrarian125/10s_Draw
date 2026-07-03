#include "SelectScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"

SelectScene::SelectScene()
    : bgImage_00(-1)
    , bgImage_01(-1)
    , isExitDialogVisible(false)
    , currentSelect(0)
    , seEasyImg(-1)
    , seNormalImg(-1)
    , seHardImg(-1)
    , seDefaultImg(-1)
    , bgScrollX(0.0f) // 初期位置
{
    // 背景画像のロード
    bgImage_00 = LoadGraph("data/Select/BG_Se_00.png");
    bgImage_01 = LoadGraph("data/Select/BG_Se_01.png");

    // メニューのボタン配置設定
    int bx = 50;  // ボタンのX座標
    int by = 400; // Y座標
    int bw = 400; // ボタンの幅
    int bh = 90;  // ボタンの高さ
    int bi = 100; // ボタン間隔

    // ボタン画像のロード
    int btnImg_b_se_00 = LoadGraph("data/Select/UI_se_00.png");
    int btnImg_b_se_02 = LoadGraph("data/Select/UI_se_02.png");
    int btnImg_b_se_03 = LoadGraph("data/Select/UI_se_03.png");
    int btnImg_b_se_04 = LoadGraph("data/Select/UI_se_04.png");

    // 各難易度の解説用画像をロード
    seEasyImg = LoadGraph("data/Select/UI_se_Easy.png");
    seNormalImg = LoadGraph("data/Select/UI_se_Normal.png");
    seHardImg = LoadGraph("data/Select/UI_se_Hard.png");
    seDefaultImg = LoadGraph("data/Select/UI_se_Default.png");

    // [0] 左上の戻るボタン
    auto b_se_00 = new GuiButton(20, 0, 100, 100, "Back");
    b_se_00->SetImage(btnImg_b_se_00);
    b_se_00->onClick = []() { SceneManager::ChangeScene("TITLE"); };
    buttons.push_back(b_se_00);

    // [1] 説明書きボタン
    auto b_se_01 = new GuiButton(bx, 180, bw, 200, "Help");
	b_se_01->SetIgnoreDimming(true);//常に明るくする
    b_se_01->SetImage(seDefaultImg);
    b_se_01->onClick = []() { SceneManager::ChangeScene("HELP"); };
    buttons.push_back(b_se_01);

    // [2] かんたん
    auto b_se_02 = new GuiButton(bx, by, bw, bh, "Easy");
    b_se_02->SetImage(btnImg_b_se_02);
    b_se_02->onClick = []() { SceneManager::ChangeScene("PLAY"); };
    buttons.push_back(b_se_02);

    // [3] ふつう
    auto b_se_03 = new GuiButton(bx, by + bi, bw, bh, "Normal");
    b_se_03->SetImage(btnImg_b_se_03);
    b_se_03->onClick = []() { SceneManager::ChangeScene("PLAY"); };
    buttons.push_back(b_se_03);

    // [4] むずかしい
    auto b_se_04 = new GuiButton(bx, by + bi * 2, bw, bh, "Hard");
    b_se_04->SetImage(btnImg_b_se_04);
    b_se_04->onClick = []() { SceneManager::ChangeScene("PLAY"); };
    buttons.push_back(b_se_04);
}

SelectScene::~SelectScene()
{
    // メモリ解放と画像削除
    DeleteGraph(bgImage_00);
    DeleteGraph(bgImage_01);
    DeleteGraph(seEasyImg);
    DeleteGraph(seNormalImg);
    DeleteGraph(seHardImg);
    DeleteGraph(seDefaultImg);
}

void SelectScene::Update()
{
    // 通常時の処理
    for (auto b : buttons) {
        b->Update();
    }

    // 上下キーで選択切り替え
    if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
        currentSelect = (currentSelect + 1) % buttons.size();
    }
    if (Input::IsKeyDown(KEY_INPUT_UP)) {
        currentSelect = (currentSelect - 1 + (int)buttons.size()) % (int)buttons.size();
    }

    // マウスオーバーとキーボード選択の同期
    for (int i = 0; i < (int)buttons.size(); i++) {
        buttons[i]->SetFocus(i == currentSelect);
        if (buttons[i]->IsMouseOver()) currentSelect = i;
    }

    // 選択状態に応じて「目標の中心座標」と「Help画像」を設定
    float targetCenterX = 640.0f; // デフォルト（画面の中心＝背景の左端近く）

    if (buttons.size() > 1) {
        if (currentSelect == 2) {         // Easy
            buttons[1]->SetImage(seEasyImg);
            targetCenterX = 1000.0f;
        }
        else if (currentSelect == 3) {    // Normal
            buttons[1]->SetImage(seNormalImg);
            targetCenterX = 2500.0f;
        }
        else if (currentSelect == 4) {    // Hard
            buttons[1]->SetImage(seHardImg);
            targetCenterX = 4000.0f;
        }
        else {                            // それ以外（Back、Help自身）
            buttons[1]->SetImage(seDefaultImg);
            targetCenterX = 640.0f;
        }
    }

    //中心座標から、画面の左端の座標（カメラ位置）に変換
    float targetX = targetCenterX - 640.0f;

    // 背景画像の範囲（0 〜 3840）からはみ出さないように制限
    if (targetX < 0.0f) targetX = 0.0f;
    if (targetX > 3840.0f) targetX = 3840.0f;

    //滑らかなイージング移動
    bgScrollX += (targetX - bgScrollX) * 0.05f;
}

void SelectScene::Draw()
{
        //5120*720の画像から、(bgScrollX, 0) を左上基準として 1280*720 のサイズを切り出して画面の (0,0) に描画
        DrawRectGraph(0, 0, (int)bgScrollX, 0, 1280, 720, bgImage_00, FALSE, FALSE);

        // 固定背景
        DrawExtendGraph(0, 0, 1280, 720, bgImage_01, TRUE);

        //ボタン描画
        for (auto b : buttons) b->Draw();
}