#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TestScene.h"
#include "TitleScene.h"
#include "PlayScene.h"


SceneBase* SceneFactory::CreateFirst(){
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name){
	if (name == "TEST"){
		return new TestScene();
	}
	if (name == "TITLE"){
		return new TitleScene();
	}
	if (name == "PLAY"){
		return new PlayScene();
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
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
