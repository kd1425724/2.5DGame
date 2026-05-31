#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/Ui/TitleSceneUi/TitleSceneUi.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::StageSelect
		);
	}
}

void TitleScene::Init()
{
	std::shared_ptr<TitleSceneUi> titleui = std::make_shared<TitleSceneUi>();
	//Objectセット
	AddObject(titleui);
}
