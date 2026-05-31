#include "StageSelectSceneUi.h"
#include"../../../Common/CommonAPI.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Common/Input/Input.h"

#include"Description/Description.h"
#include"Button/Button.h"

void StageSelectSceneUi::Init()
{
	//ボタン
	std::shared_ptr<StageSelectButton> button = std::make_shared<StageSelectButton>();
	SceneManager::Instance().AddObject(button);

	//ステージ１説明画像
	std::shared_ptr<StageDescription> stagedescription = std::make_shared<StageDescription>();
	stagedescription->SetButton(button);
	SceneManager::Instance().AddObject(stagedescription);
}

void StageSelectSceneUi::PreUpdate()
{

}

void StageSelectSceneUi::Update()
{
	
}

void StageSelectSceneUi::PostUpdate()
{}

void StageSelectSceneUi::DrawSprite()
{

}

