#include "SelectScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"

SelectScene::SelectScene()
    : bgImage(-1)
    , isExitDialogVisible(false)
    , currentSelect(0)
	, seEasyImg(-1)
	, seNormalImg(-1)
	, seHardImg(-1)
	, seDefaultImg(-1)
{
    //背景画像のロード
    bgImage = LoadGraph("data/Select/BG_Ti_00.png");

    //メニューのボタン配置設定
    int bx = 50;  //ボタンのX座標
    int by = 400; //Y座標
    int bw = 400; //ボタンの幅
    int bh = 90;  //ボタンの高さ
    int bi = 100; //ボタン間隔

    //ボタン画像のロード
    int btnImg_b_se_00 = LoadGraph("data/Select/UI_se_00.png");
	int btnImg_b_se_01 = LoadGraph("data/Select/UI_se_01.png");
	int btnImg_b_se_02 = LoadGraph("data/Select/UI_se_02.png");
    int btnImg_b_se_03 = LoadGraph("data/Select/UI_se_03.png");
    int btnImg_b_se_04 = LoadGraph("data/Select/UI_se_04.png");

    //各難易度の解説用画像をロード
    seEasyImg = LoadGraph("data/Select/UI_se_Easy.png");
    seNormalImg = LoadGraph("data/Select/UI_se_Normal.png");
    seHardImg = LoadGraph("data/Select/UI_se_Hard.png");
	seDefaultImg = LoadGraph("data/Select/UI_se_Default.png");

    //左上の戻るボタン
    auto b_se_00 = new GuiButton(20, 0, 100, 100, "Back");
    b_se_00->SetImage(btnImg_b_se_00);
    b_se_00->onClick = []() { SceneManager::ChangeScene("TITLE"); };
    buttons.push_back(b_se_00);

    //説明書きボタン（何もマウスオーバーしていない時、またはここをクリックした時はHELPシーンへ）
    auto b_se_01 = new GuiButton(bx, 180, bw, 200, "Help");
    b_se_01->SetImage(seDefaultImg);
    b_se_01->onClick = []() { SceneManager::ChangeScene("HELP"); };
    buttons.push_back(b_se_01);

    //かんたん
    auto b_se_02 = new GuiButton(bx, by, bw, bh, "Easy");
    b_se_02->SetImage(btnImg_b_se_02);
    b_se_02->onClick = []() {SceneManager::ChangeScene("PLAY");};
    buttons.push_back(b_se_02);

    //ふつう
    auto b_se_03 = new GuiButton(bx, by + bi, bw, bh, "Normal");
    b_se_03->SetImage(btnImg_b_se_03);
    b_se_03->onClick = []() {SceneManager::ChangeScene("PLAY");};
    buttons.push_back(b_se_03);

    //むずかしい
    auto b_se_04 = new GuiButton(bx, by + bi * 2, bw, bh, "Hard");
    b_se_04->SetImage(btnImg_b_se_04);
    b_se_04->onClick = []() {SceneManager::ChangeScene("PLAY");};
    buttons.push_back(b_se_04);
}

SelectScene::~SelectScene()
{
    //メモリ解放と画像削除
    DeleteGraph(bgImage);
	DeleteGraph(seEasyImg);
	DeleteGraph(seNormalImg);
	DeleteGraph(seHardImg);
	DeleteGraph(seDefaultImg);
}

void SelectScene::Update()
{
    //通常時の処理
    for (auto b : buttons) {
        b->Update();
    }

    //上下キーで選択切り替え
    if (Input::IsKeyDown(KEY_INPUT_DOWN)) {
        currentSelect = (currentSelect + 1) % buttons.size();
    }
    if (Input::IsKeyDown(KEY_INPUT_UP)) {
        currentSelect = (currentSelect - 1 + (int)buttons.size()) % (int)buttons.size();
    }

    //マウスオーバーとキーボード選択の同期
    for (int i = 0; i < (int)buttons.size(); i++) {
        buttons[i]->SetFocus(i == currentSelect);
        if (buttons[i]->IsMouseOver()) currentSelect = i;
    }

    //選択状態に応じてHelpボタンの画像を切り替え
    if (buttons.size() > 1) {
        if (currentSelect == 2) {       //Easy
            buttons[1]->SetImage(seEasyImg);
        }
        else if (currentSelect == 3) {  //Normal
            buttons[1]->SetImage(seNormalImg);
        }
        else if (currentSelect == 4) {  //Hard
            buttons[1]->SetImage(seHardImg);
        }
        else {                          //それ以外（Back、あるいはHelp自身）
            //初期状態もしくは何も選んでいないの時に表示したい画像
            buttons[1]->SetImage(seDefaultImg);
        }
    }
}

void SelectScene::Draw()
{
    //背景描画
    DrawExtendGraph(0, 0, 1280, 720, bgImage, FALSE);

    //ボタン描画
    for (auto b : buttons) b->Draw();
}