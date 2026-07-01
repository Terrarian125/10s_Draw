#include "HelpScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"


HelpScene::HelpScene()
{
    //背景画像のロード
    bgImage = LoadGraph("data/help/BG_he_00.png");

    //メニューのボタン配置設定
    int bx = 50;  //ボタンのX座標
    int by = 150; //Y座標
    int bw = 400; //ボタンの幅
    int bh = 90;  //ボタンの高さ
    int bi = 100; //ボタン間隔

    //ボタン画像のロード
    int btnImg_b_he_00 = LoadGraph("data/help/UI_he_00.png");
    int btnImg_b_he_01 = LoadGraph("data/help/UI_he_01.png");
    int btnImg_b_he_02 = LoadGraph("data/help/UI_he_02.png");
    int btnImg_b_he_03 = LoadGraph("data/help/UI_he_03.png");
    int btnImg_b_he_04 = LoadGraph("data/help/UI_he_04.png");
	int btnImg_b_he_05 = LoadGraph("data/help/UI_he_05.png");

    //解説用画像をロード
    help00 = LoadGraph("data/help/Help_00.png");
    help01 = LoadGraph("data/help/Help_01.png");
    help02 = LoadGraph("data/help/Help_02.png");
    help03 = LoadGraph("data/help/Help_03.png");
	help04 = LoadGraph("data/help/Help_04.png");
	help05 = LoadGraph("data/help/Help_05.png");

    //左上の戻るボタン
    auto b_he_00 = new GuiButton(20, 0, 100, 100, "Back");
    b_he_00->SetImage(btnImg_b_he_00);
    b_he_00->onClick = []() { SceneManager::ChangeScene("TITLE"); };
    buttons.push_back(b_he_00);

    //説明書きボタン
    auto b_he_01 = new GuiButton(600, 150, 600, 500, "Help");
    b_he_01->SetImage(help01);
    b_he_01->onClick = []() {};
    buttons.push_back(b_he_01);

    //ゲームの説明①
    auto b_he_02 = new GuiButton(bx, by, bw, bh, "1");
    b_he_02->SetImage(btnImg_b_he_02);
    b_he_02->onClick = []() {};
    buttons.push_back(b_he_02);

	//ゲームの説明②
    auto b_he_03 = new GuiButton(bx, by + bi, bw, bh, "2");
    b_he_03->SetImage(btnImg_b_he_03);
    b_he_03->onClick = []() {};
    buttons.push_back(b_he_03);

	//Arcade説明
    auto b_he_04 = new GuiButton(bx, by + bi * 2, bw, bh, "3");
    b_he_04->SetImage(btnImg_b_he_04);
    b_he_04->onClick = []() {};
    buttons.push_back(b_he_04);

    //VSの説明
    auto b_he_05 = new GuiButton(bx, by + bi * 3, bw, bh, "4");
    b_he_05->SetImage(btnImg_b_he_05);
    b_he_05->onClick = []() {};
    buttons.push_back(b_he_05);
}

HelpScene::~HelpScene()
{
    //メモリ解放と画像削除
    DeleteGraph(bgImage);
}

void HelpScene::Update()
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

    // 選択状態に応じてHelp画像（buttons[1]）の画像を切り替え
    if (buttons.size() > 1) {
        if (currentSelect == 2) {       // ボタン「1」
            buttons[1]->SetImage(help00);
        }
        else if (currentSelect == 3) {  // ボタン「2」
            buttons[1]->SetImage(help01);
        }
        else if (currentSelect == 4) {  // ボタン「3」
            buttons[1]->SetImage(help02);
        }
        else if (currentSelect == 5) {  // ボタン「4」
            buttons[1]->SetImage(help03);
        }
        else if (currentSelect == 6) {  // ボタン「5」
            buttons[1]->SetImage(help04);
        }
        else if (currentSelect == 7) {  // ボタン「6」
            buttons[1]->SetImage(help05);
        }
        else {                          // それ以外
            buttons[1]->SetImage(helpDe);
        }
    }
}

void HelpScene::Draw()
{
    // 背景描画
    DrawExtendGraph(0, 0, 1280, 720, bgImage, FALSE);

    // ボタン描画
    for (auto b : buttons) b->Draw();
}