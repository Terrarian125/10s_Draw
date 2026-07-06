#include "PlayScene.h"
#include "MenuLayout.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"
#include "Time.h"

PlayScene::PlayScene()
    : bgImage_00(-1), ui_pl_01(-1), ui_pl_02(-1), ryeFontHandle(-1)
    , startTime(0), gameTimer(0.0f), fadeAlpha(255), uiAlpha(255)
    , state(PlayState::Playing) //初期状態はPlaying
    , pauseLayout(nullptr)
    , resultLayout(nullptr)
{
    //背景とUI素材のロード
    bgImage_00 = LoadGraph("data/play/BG_pl_00.png");
    ui_pl_01 = LoadGraph("data/play/UI_pl_01.png");
    ui_pl_02 = LoadGraph("data/play/UI_pl_02.png");

    //Ryeフォントの動的読み込み
    const char* fontPath = "data/Rye-Regular.ttf";
    if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
        ryeFontHandle = CreateFontToHandle("Rye", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    }
    else {
        ryeFontHandle = CreateFontToHandle(NULL, 60, 3);
    }

    //シーン開始時刻を記録
    startTime = GetNowHiPerformanceCount();

    //戻るボタンをPauseボタンに変更（設計プラン通りのonClick処理を実装）
    int btnImg_b_pl_00 = LoadGraph("data/play/UI_pl_00.png");
    auto b_pl_00 = new GuiButton(20, 0, 100, 100, "pause");
    b_pl_00->SetImage(btnImg_b_pl_00);

    b_pl_00->onClick = [this]()
        {
            if (state != PlayState::Playing)
                return;

            state = PlayState::Pause;

            //リトライが押された時に、メニューを閉じてその場でPlaySceneの初期化
            pauseLayout = new PauseLayout([this]()
                {
                    state = PlayState::Playing;

                    if (pauseLayout)
                    {
                        pauseLayout->DestroyMe();
                        pauseLayout = nullptr;
                    }

                    //変数をその場でリセット
                    startTime = GetNowHiPerformanceCount(); //シーン開始時間を現在の時刻でリセット
                    gameTimer = 0.0f;                       //タイマー表示を0に戻す
                    fadeAlpha = 255;                        //フェードインの黒ベタを復活
                    uiAlpha = 255;                          //UI透過度を初期に戻す
                });
        };
    buttons.push_back(b_pl_00);
}

PlayScene::~PlayScene()
{
    DeleteGraph(bgImage_00);
    DeleteGraph(ui_pl_01);
    DeleteGraph(ui_pl_02);
    DeleteFontToHandle(ryeFontHandle);
    RemoveFontResourceEx("data/font/Rye-Regular.ttf", FR_PRIVATE, NULL);

    //生成されたレイアウトが残っていれば安全に解放
    if (pauseLayout) { pauseLayout->DestroyMe(); pauseLayout = nullptr; }
    if (resultLayout) { resultLayout->DestroyMe(); resultLayout = nullptr; }

    buttons.clear();
}

void PlayScene::Update()
{
    //ポーズ中はゲームを止める
    if (state == PlayState::Pause)
    {
        startTime += (LONGLONG)(Time::DeltaTime() * 1000000.0f);

        for (auto b : buttons)
            b->Update();

        return;
    }

    //リザルト中もゲームの更新を止める
    if (state == PlayState::Result)
    {
        return;
    }

    //PlayState::Playing（通常更新、勝敗判定、20秒判定）
    LONGLONG nowTime = GetNowHiPerformanceCount();
    float elapsedSec = (float)(nowTime - startTime) / 1000000.0f; //経過秒数

    //画面全体のフェードイン (1秒間)
    if (elapsedSec <= 1.0f) {
        fadeAlpha = 255 - (int)(elapsedSec * 255);
    }
    else {
        fadeAlpha = 0;
    }

    //カウントアップとUI_pl_02のタイムライン制御（元の時間を壊さない安全なロジック）
    if (elapsedSec >= 3.0f) {
        float countTime = elapsedSec - 3.0f; //カウント開始からの秒数

        if (countTime < 4.5f) {
            gameTimer = countTime;
            uiAlpha = 255 - (int)((countTime / 4.5f) * 255);
        }
        else if (countTime >= 4.5f && countTime < 20.0f) {
            gameTimer = countTime;
            uiAlpha = 0; //完全にみえない
        }
        else {
            gameTimer = 20.0f;
            uiAlpha = 255; //再表示
        }
    }

    //20秒経過でリザルト画面
    if (gameTimer >= 20.0f && state != PlayState::Result)
    {
        state = PlayState::Result;

        resultLayout = new ResultLayout(false, false, 20.0f);
    }

    //Pauseボタンなどの通常更新
    for (auto b : buttons) b->Update();
}

void PlayScene::Draw()
{
    //背景はどの状態でも常に最背面に描画
    DrawGraph(0, 0, bgImage_00, FALSE);

    //Drawのステートマシン分岐（設計書通りに配置。各Layoutは自動描画されます）
    switch (state)
    {
    case PlayState::Playing:
        //ゲーム描画
        break;

    case PlayState::Pause:
        //ゲーム描画
        break;

    case PlayState::Result:
        //ゲーム描画
        break;
    }

    //ゲーム本編・UIの表示
    LONGLONG nowTime = GetNowHiPerformanceCount();
    float elapsedSec = (float)(nowTime - startTime) / 1000000.0f;

    if (elapsedSec < 3.0f) {
        DrawGraph(0, 0, ui_pl_01, TRUE);
    }
    else {
        if (elapsedSec >= 23.0f) {
            DrawFormatStringToHandle(590, 120, GetColor(60, 40, 20), ryeFontHandle, "%04.1f", gameTimer);
        }
        else {
            if (uiAlpha > 0) {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, uiAlpha);
                DrawGraph(0, 0, ui_pl_02, TRUE);
                DrawFormatStringToHandle(590, 120, GetColor(60, 40, 20), ryeFontHandle, "%04.1f", gameTimer);
                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            }
        }
    }

    //ボタン描画
    for (auto b : buttons) b->Draw();

    //画面全体のフェードイン用黒ベタ
    if (fadeAlpha > 0) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
        DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}