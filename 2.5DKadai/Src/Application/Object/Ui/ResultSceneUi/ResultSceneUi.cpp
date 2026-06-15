#include "ResultSceneUi.h"
#include"../CommonUi/BlackBack/BlackBack.h"
#include"../../../Scene/SceneManager.h"
void ResultSceneUi::Init()
{
	std::shared_ptr<BlackBack> blackback = std::make_shared<BlackBack>();
	blackback->Init();
	SceneManager::Instance().AddObject(blackback);

	

}
