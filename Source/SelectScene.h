#pragma once
#include "../Library/SceneBase.h"
#include "../Library/GuiButton.h"
#include <vector>

class SelectScene : public SceneBase
{
public:
    SelectScene();
    ~SelectScene();

    void Update() override;
    void Draw() override;

private:
    int bgImage_00;                     // 背景画像のグラフィックハンドル
    int bgImage_01;
    float bgScrollX;
    std::vector<GuiButton*> buttons; // メインメニューのボタン配列

    // 終了確認ダイアログ関連
    bool isExitDialogVisible;        // ダイアログの表示フラグ
    int currentSelect;               // キーボード選択用インデックス

	// ヘルプ画像のグラフィックハンドル
	int seEasyImg = -1;    //かんたん用のヘルプ画像
	int seNormalImg = -1;  //ふつう用のヘルプ画像
	int seHardImg = -1;    //むずかしい用のヘルプ画像
	int seDefaultImg = -1; //デフォルトのヘルプ画像（何も選択していない時に表示する）
};