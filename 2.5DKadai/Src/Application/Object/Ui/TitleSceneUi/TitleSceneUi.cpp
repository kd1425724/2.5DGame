#include "TitleSceneUi.h"
#include"TitleLogo/TitleLogo.h"
#include"PressEnter/PressEnter.h"
#include"../../../Scene/SceneManager.h"

void TitleSceneUi::Init()
{
	//タイトルロゴ
	std::shared_ptr<TitleLogo> titlelogo = std::make_shared<TitleLogo>();
	titlelogo->Init();
	//SceneManager::Instance().AddObject(titlelogo);
	
	//PressAny
	std::shared_ptr<PressEnter> pressenter = std::make_shared<PressEnter>();
	pressenter->Init();
	SceneManager::Instance().AddObject(pressenter);
}
