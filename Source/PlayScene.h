#pragma once
#include "../Library/SceneBase.h"
#include "../Library/GuiButton.h"
#include <vector>

// クラスの前方宣言
class SettingPanel;

/// <summary>
/// テストシーンクラス
/// </summary>
class PlayScene : public SceneBase
{
public:
    PlayScene();
    ~PlayScene();

    void Update() override;
    void Draw() override;

private:
    int bgImage;                     // 背景画像のグラフィックハンドル
    std::vector<GuiButton*> buttons; // メインメニューのボタン配列

    // 設定パネル関連
    SettingPanel* mySettingPanel;    // 設定パネル

    // 終了確認ダイアログ関連
    bool isExitDialogVisible;        // ダイアログの表示フラグ
    int currentSelect;               // キーボード選択用インデックス

	// ヘルプ画像のグラフィックハンドル
    int helpEasyImg = -1;
    int helpNormalImg = -1;
    int helpHardImg = -1;
	int helpDefaultImg = -1;
};