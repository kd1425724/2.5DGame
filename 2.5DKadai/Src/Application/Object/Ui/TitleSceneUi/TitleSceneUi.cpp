#include "TitleSceneUi.h"
#include"TitleLogo/TitleLogo.h"
#include"PressAny/PressAny.h"
#include"../../../Scene/SceneManager.h"

void TitleSceneUi::Init()
{
	//タイトルロゴ
	std::shared_ptr<TitleLogo> titlelogo = std::make_shared<TitleLogo>();
	titlelogo->Init();
	SceneManager::Instance().AddObject(titlelogo);
	
	//PressAny
	std::shared_ptr<PressAny> pressany = std::make_shared<PressAny>();
	pressany->Init();
	SceneManager::Instance().AddObject(pressany);
}
