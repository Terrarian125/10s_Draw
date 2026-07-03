#pragma once
#include "../Library/SceneBase.h"
#include "../Library/GuiButton.h"
#include <vector>

class HelpScene : public SceneBase
{
public:
    HelpScene();
    ~HelpScene();

    void Update() override;
    void Draw() override;

private:
    int bgImage_00;                     // 背景画像のグラフィックハンドル
    int bgImage_01;
    int bgScrollX;
    std::vector<GuiButton*> buttons; // ボタン配列
    int currentSelect;               // キーボード選択用インデックス

	// 解説用画像のグラフィックハンドル
	int helpDe = -1; //解説用のデフォルト画像
    int help00 = -1;
    int help01 = -1;
    int help02 = -1;
	int help03 = -1;
	int help04 = -1;
	int help05 = -1;
};