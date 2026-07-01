#include "PlayScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"
#include "../Library/GameSetting.h"
#include "SettingPanel.h"

PlayScene::PlayScene()
    : bgImage(-1)
    , mySettingPanel(nullptr)
    , isExitDialogVisible(false)
    , currentSelect(0)
    , helpEasyImg(-1)
    , helpNormalImg(-1)
    , helpHardImg(-1)
{
    //背景画像のロード
    bgImage = LoadGraph("data/Play/BG_Ti_00.png");

    //メニューのボタン配置設定
    int bx = 50;  //ボタンのX座標
    int by = 400; //Y座標
    int bw = 400; //ボタンの幅
    int bh = 90;  //ボタンの高さ
    int bi = 100; //ボタン間隔

    //ボタン画像のロード
    int btnImg_b_pl_00 = LoadGraph("data/play/UI_pl_00.png");
	int btnImg_b_pl_01 = LoadGraph("data/play/UI_pl_01.png");
	int btnImg_b_pl_02 = LoadGraph("data/play/UI_pl_02.png");
    int btnImg_b_pl_03 = LoadGraph("data/play/UI_pl_03.png");
    int btnImg_b_pl_04 = LoadGraph("data/play/UI_pl_04.png");

    //各難易度の解説用画像をロード
    helpEasyImg = LoadGraph("data/play/Help_Easy.png");
    helpNormalImg = LoadGraph("data/play/Help_Normal.png");
    helpHardImg = LoadGraph("data/play/Help_Hard.png");
	helpDefaultImg = LoadGraph("data/play/Help_Default.png");

    //左上の戻るボタン
    auto b_pl_00 = new GuiButton(20, 20, 100, 60, "Back");
    b_pl_00->SetImage(btnImg_b_pl_00);
    b_pl_00->onClick = []() { SceneManager::ChangeScene("TITLE"); };
    buttons.push_back(b_pl_00);

    //説明書きボタン（何もマウスオーバーしていない時、またはここをクリックした時はHELPシーンへ）
    auto b_pl_01 = new GuiButton(bx, 180, bw, 200, "Help");
    b_pl_01->SetImage(btnImg_b_pl_01);
    b_pl_01->onClick = []() { SceneManager::ChangeScene("HELP"); };
    buttons.push_back(b_pl_01);

    //かんたん
    auto b_pl_02 = new GuiButton(bx, by, bw, bh, "Easy");
    b_pl_02->SetImage(btnImg_b_pl_02);
    b_pl_02->onClick = []() {};
    buttons.push_back(b_pl_02);

    //ふつう
    auto b_pl_03 = new GuiButton(bx, by + bi, bw, bh, "Normal");
    b_pl_03->SetImage(btnImg_b_pl_03);
    b_pl_03->onClick = []() {};
    buttons.push_back(b_pl_03);

    //むずかしい
    auto b_pl_04 = new GuiButton(bx, by + bi * 2, bw, bh, "Hard");
    b_pl_04->SetImage(btnImg_b_pl_04);
    b_pl_04->onClick = []() {};
    buttons.push_back(b_pl_04);
}

PlayScene::~PlayScene()
{
    //メモリ解放と画像削除
    DeleteGraph(bgImage);
    DeleteGraph(helpEasyImg);
    DeleteGraph(helpNormalImg);
    DeleteGraph(helpHardImg);
}

void PlayScene::Update()
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
            buttons[1]->SetImage(helpEasyImg);
        }
        else if (currentSelect == 3) {  //Normal
            buttons[1]->SetImage(helpNormalImg);
        }
        else if (currentSelect == 4) {  //Hard
            buttons[1]->SetImage(helpHardImg);
        }
        else {                          //それ以外（Back、あるいはHelp自身）
            //初期状態もしくは何も選んでいないの時に表示したい画像
            buttons[1]->SetImage(LoadGraph("data/play/Help_Default.png"));
        }
    }
}

void PlayScene::Draw()
{
    //背景描画
    DrawExtendGraph(0, 0, 1280, 720, bgImage, FALSE);

    //ボタン描画
    for (auto b : buttons) b->Draw();
}