#include "TitleSceneUi.h"
#include"TitleLogo/TitleLogo.h"
#include"PressEnter/PressEnter.h"
#include"../../../Scene/SceneManager.h"

void TitleSceneUi::Init()
{
	//タイトルロゴ
	std::shared_ptr<TitleLogo> titlelogo = std::make_shared<TitleLogo>();
	titlelogo->Init();
	titlelogo->SetPos({ 0,200,0 });
	titlelogo->SetSize(0.8f);
	SceneManager::Instance().AddObject(titlelogo);
	
	//PressEnter
	std::shared_ptr<PressEnter> pressenter = std::make_shared<PressEnter>();
	pressenter->Init();
	pressenter->SetPos({ 0,-200,0 });
	pressenter->SetSize(0.8f);
	SceneManager::Instance().AddObject(pressenter);
}
