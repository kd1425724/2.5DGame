#include "StageSelectScene.h"
#include"../../Object/Ui/StageSelectSceneUi/StageSelectSceneUi.h"
#include"../SceneManager.h"
#include"../../Object/BackGround/StageSelectSceneBackGround/StageSelectSceneBackGround.h"
#include"../../Common/Info/Info.h"
#include"../../Manager/StageManager/StageManager.h"


void StageSelectScene::Event()
{
	//UIまとめ
	m_stageselectui->Update();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		return;
	}
}

void StageSelectScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);

	m_stageselectui = std::make_shared<StageSelectSceneUi>();
	m_stageselectui->Init();

	//背景
	std::shared_ptr<StageSelectSceneBackGround> background = std::make_shared<StageSelectSceneBackGround>();
	background->Init();
	m_objList.push_back(background);

	//一部屋ロード
	STAGEMANAGER.LoadRoom("Box");

	//スクロールするかどうか
	INFO.SetScrollFlg(false);
}
