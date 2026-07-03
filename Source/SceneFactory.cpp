#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TestScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "HelpScene.h"	


SceneBase* SceneFactory::CreateFirst(){
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name){
	///
	/// RETURNで直前のシーンに戻る機能追加
	/// ここではRETURNの処理はしない。SceneManagerで処理する
	///
	if (name == "TEST"){
		return new TestScene();
	}
	if (name == "TITLE"){
		return new TitleScene();
	}
	if (name == "SELECT"){
		return new SelectScene();
	}
	if (name == "PLAY"){
		return new PlayScene();
	}
	if (name == "HELP"){
		return new HelpScene();
	}



	//if (name == ""){
	//	return new ();
	//}
	//if (name == ""){
	//	return new ();
	//}
	//if (name == ""){
	//	return new ();
	//}
	MessageBox(NULL, ("次のシーンはありません\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
