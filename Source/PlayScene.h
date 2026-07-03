#pragma once
#include "../Library/SceneBase.h"
#include "../Library/GuiButton.h"
#include <vector>

class PlayScene : public SceneBase
{
public:
    PlayScene();
    ~PlayScene();

    void Update() override;
    void Draw() override;

private:
    int bgImage_00;
    int ui_pl_01, ui_pl_02;
    int ryeFontHandle;      // Ryeフォント用
    
    LONGLONG startTime;     // シーン開始時間
    float gameTimer;        // 00.0用の数値
    int fadeAlpha;          // 画面全体のフェードイン用
    int uiAlpha;            // UI_pl_02とタイマーの透過度用
    std::vector<GuiButton*> buttons; // ボタン配列
};