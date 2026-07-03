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
    int bgImage_00;                     // 背景画像のグラフィックハンドル
    int bgImage_01;
    int bgScrollX;
    std::vector<GuiButton*> buttons; // ボタン配列
};