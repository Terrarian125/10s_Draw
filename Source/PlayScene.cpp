#include "PlayScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"

PlayScene::PlayScene() 
	: bgImage_00(-1)
{
    //背景画像のロード
    bgImage_00 = LoadGraph("data/play/BG_pl_00.png");

    //メニューのボタン配置設定
    int bx = 50;  //ボタンのX座標
    int by = 400; //Y座標
    int bw = 400; //ボタンの幅
    int bh = 90;  //ボタンの高さ
    int bi = 100; //ボタン間隔

    //ボタン画像のロード
    int btnImg_b_pl_00 = LoadGraph("data/play/UI_pl_00.png");

    //左上の戻るボタン
    auto b_pl_00 = new GuiButton(20, 0, 100, 100, "Back");
    b_pl_00->SetImage(btnImg_b_pl_00);
    b_pl_00->onClick = []() { SceneManager::ChangeScene("RETURN"); };
    buttons.push_back(b_pl_00);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}
