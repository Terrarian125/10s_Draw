#include "PlayScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"

PlayScene::PlayScene()
    : bgImage_00(-1), ui_pl_01(-1), ui_pl_02(-1), ryeFontHandle(-1)
    , startTime(0), gameTimer(0.0f), fadeAlpha(255), uiAlpha(255)
{
    //背景とUI素材のロード
    bgImage_00 = LoadGraph("data/play/BG_pl_00.png");
    ui_pl_01 = LoadGraph("data/play/UI_pl_01.png");
    ui_pl_02 = LoadGraph("data/play/UI_pl_02.png");

    //Ryeフォントの動的読み込み (PCに入っていなくても一時的に使用可能にする)
    const char* fontPath = "data/Rye-Regular.ttf";
    if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
        ryeFontHandle = CreateFontToHandle("Rye", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    }
    else {
        //読み込めなかった場合のフォールバック
        ryeFontHandle = CreateFontToHandle(NULL, 60, 3);
    }

    //シーン開始時刻を記録
    startTime = GetNowHiPerformanceCount();

    // 戻るボタン
    int btnImg_b_pl_00 = LoadGraph("data/play/UI_pl_00.png");
    auto b_pl_00 = new GuiButton(20, 0, 100, 100, "Back");
    b_pl_00->SetImage(btnImg_b_pl_00);
    b_pl_00->onClick = []() { SceneManager::ChangeScene("TITLE"); };
    buttons.push_back(b_pl_00);
}

PlayScene::~PlayScene()
{
    DeleteGraph(bgImage_00);
    DeleteGraph(ui_pl_01);
    DeleteGraph(ui_pl_02);
    DeleteFontToHandle(ryeFontHandle);
    //フォントのリソース解放
    RemoveFontResourceEx("data/font/Rye-Regular.ttf", FR_PRIVATE, NULL);
}

void PlayScene::Update()
{
    LONGLONG nowTime = GetNowHiPerformanceCount();
    float elapsedSec = (float)(nowTime - startTime) / 1000000.0f; // 経過秒数

    //画面全体のフェードイン (1秒間)
    if (elapsedSec <= 1.0f) {
        fadeAlpha = 255 - (int)(elapsedSec * 255);
    }
    else {
        fadeAlpha = 0;
    }

    //カウントアップとUI_pl_02のタイムライン制御
    if (elapsedSec >= 3.0f) {
        float countTime = elapsedSec - 3.0f; // カウント開始（UI_pl_02出現）からの秒数

        // 【タイマーとアルファ状態の分岐】
        if (countTime < 4.5f) {
            //0.0秒 〜 4.5秒：カウントアップしつつ、徐々に薄くする
            gameTimer = countTime;
            uiAlpha = 255 - (int)((countTime / 4.5f) * 255);
        }
        else if (countTime >= 4.5f && countTime < 20.0f) {
            //4.5秒 〜 20.0秒：画面からは消えるが、裏でカウントアップは継続
            gameTimer = countTime;
            uiAlpha = 0; // 完全にみえない
        }
        else {
            //20.0秒以降：20.0秒でカウントをストップし、再びパッと表示する
            gameTimer = 20.0f;
            uiAlpha = 255; // 再表示
        }
    }

    for (auto b : buttons) b->Update();
}

void PlayScene::Draw()
{
    //背景
    DrawGraph(0, 0, bgImage_00, FALSE);

    LONGLONG nowTime = GetNowHiPerformanceCount();
    float elapsedSec = (float)(nowTime - startTime) / 1000000.0f;

    //UI表示ロジック
    if (elapsedSec < 3.0f) {
        // 最初の3秒間は UI_pl_01 を表示
        DrawGraph(0, 0, ui_pl_01, TRUE);
    }
    else {
        //3秒経過後（カウント開始後）の処理

        if (elapsedSec >= 23.0f) {
            //【20秒経過後（3秒 + 20秒 = 23秒以降）】
            // 看板(UI_pl_02)は描画せず、ストップした文字だけをパッと完全不透明で描画
            DrawFormatStringToHandle(590, 120, GetColor(60, 40, 20), ryeFontHandle, "%04.1f", gameTimer);
        }
        else {
            //【0秒 〜 20秒未満の間】（4.5秒かけて消えるフェードアウト期間など）
            // uiAlpha が 0 より大きい時だけ、看板と文字をセットで透過描画
            if (uiAlpha > 0) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, uiAlpha);

                // 看板UIの描画
                DrawGraph(0, 0, ui_pl_02, TRUE);

                // カウントアップ文字 (Ryeフォント)
                DrawFormatStringToHandle(590, 120, GetColor(60, 40, 20), ryeFontHandle, "%04.1f", gameTimer);

                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
    }

    // ボタン描画
    for (auto b : buttons) b->Draw();

    // 画面全体のフェードイン用黒ベタ
    if (fadeAlpha > 0) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
        DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}