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
    int bgImage;                     // 背景画像のグラフィックハンドル
    std::vector<GuiButton*> buttons; // ボタン配列
};