#include "MenuLayout.h"
#include <DxLib.h>
#include "../Library/SceneManager.h"

// ==========================================
// ポーズレイアウトの実装
// ==========================================
PauseLayout::PauseLayout(std::function<void()> onRetryAction) {
    int bx = 490;
    int by = 250;
    int bw = 300;
    int bh = 50;
    int bi = 70;

    //描画順を通常オブジェクト（10）より手前（数値の小さい方）に設定
    SetDrawOrder(5);

    //押されたら、PlaySceneから渡された「メニューを閉じてリセットする」処理を実行する
    auto bRetry = new GuiButton(bx, by, bw, bh, "Retry");
    bRetry->onClick = onRetryAction;
    bRetry->SetDrawOrder(1); // 暗幕レイアウトよりさらに手前に描画
    buttons.push_back(bRetry);

    //設定画面
    auto bSetting = new GuiButton(bx, by + bi, bw, bh, "Settings");
    bSetting->onClick = []() { /* 設定処理 */ };
    bSetting->SetDrawOrder(1);
    buttons.push_back(bSetting);

    //遊び方
    auto bHelp = new GuiButton(bx, by + bi * 2, bw, bh, "How to Play");
    bHelp->onClick = []() { SceneManager::ChangeScene("HELP"); };
    bHelp->SetDrawOrder(1);
    buttons.push_back(bHelp);

    //ステージセレクトへ戻る
    auto bSelect = new GuiButton(bx, by + bi * 3, bw, bh, "Stage Select");
    bSelect->onClick = []() { SceneManager::ChangeScene("SELECT"); };
    bSelect->SetDrawOrder(1);
    buttons.push_back(bSelect);
}

PauseLayout::~PauseLayout() {
    //レイアウト（暗幕）が削除される時、生成したボタンも道連れで安全に消去する
    for (auto b : buttons) {
        if (b) b->DestroyMe();
    }
    buttons.clear();
}

void PauseLayout::Update() {
}

void PauseLayout::Draw() {
    //暗幕の描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //メニューウィンドウ背景
    DrawBox(440, 150, 840, 580, GetColor(30, 30, 30), TRUE);
    DrawBox(440, 150, 840, 580, GetColor(255, 255, 255), FALSE);

    DrawString(590, 180, "PAUSE", GetColor(255, 255, 255));
}

// ==========================================
// リザルトレイアウトの実装
// ==========================================
ResultLayout::ResultLayout(bool isWin, bool hasNextStage, float finalTime)
    : isWinResult(isWin), scoreTime(finalTime)
{
    int bx = 490;
    int by = 300;
    int bw = 300;
    int bh = 50;

    //ポーズ同様、手前に描画
    SetDrawOrder(5);

    if (isWin) {
        if (hasNextStage) {
            auto bNext = new GuiButton(bx, by, bw, bh, "Next Match");
            bNext->onClick = []() { SceneManager::ChangeScene("PLAY"); };
            bNext->SetDrawOrder(1);
            buttons.push_back(bNext);
        }
        auto bSelect = new GuiButton(bx, by + 70, bw, bh, "Stage Select");
        bSelect->onClick = []() { SceneManager::ChangeScene("SELECT"); };
        bSelect->SetDrawOrder(1);
        buttons.push_back(bSelect);
    }
    else {
        auto bSelect = new GuiButton(bx, by, bw, bh, "Back to Stage Select");
        bSelect->onClick = []() { SceneManager::ChangeScene("SELECT"); };
        bSelect->SetDrawOrder(1);
        buttons.push_back(bSelect);
    }
}

ResultLayout::~ResultLayout() {
    for (auto b : buttons) {
        if (b) b->DestroyMe();
    }
    buttons.clear();
}

void ResultLayout::Update() {
}

void ResultLayout::Draw() {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawBox(440, 150, 840, 580, GetColor(40, 20, 20), TRUE);
    DrawBox(440, 150, 840, 580, GetColor(200, 150, 50), FALSE);

    DrawString(580, 180, "RESULT", GetColor(255, 215, 0));
    DrawFormatString(540, 230, GetColor(255, 255, 255), "Clear Time: %.1fs", scoreTime);
}