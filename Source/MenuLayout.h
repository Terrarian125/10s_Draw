#pragma once
#include "../Library/GuiButton.h"
#include <vector>
#include <functional>

// ==========================================
// ポーズ画面のレイアウトクラス
// ==========================================
class PauseLayout : public GameObject {
public:
    // コンストラクタで「閉じる（再開）ときのアクション」を受け取る
    PauseLayout(std::function<void()> onResumeAction);
    ~PauseLayout() override;

    void Update() override;
    void Draw() override;

private:
    std::vector<GuiButton*> buttons;
};

// ==========================================
// リザルト画面のレイアウトクラス
// ==========================================
class ResultLayout : public GameObject {
public:
    ResultLayout(bool isWin, bool hasNextStage, float finalTime);
    ~ResultLayout() override;

    void Update() override;
    void Draw() override;

private:
    std::vector<GuiButton*> buttons;
    bool isWinResult;
    float scoreTime;
};