#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/Ui/TitleSceneUi/TitleSceneUi.h"
#include"../../Object/BackGround/TitleSceneBackGround/TitleSceneBackGround.h"
#include"../../Manager/StageManager/StageManager.h"
#include"../../Common/Info/Info.h"
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
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);

	//std::shared_ptr<TitleSceneUi> titlesceneui = std::make_shared<TitleSceneUi>();
	//titlesceneui->Init();

	//背景
	std::shared_ptr<TitleSceneBackGround> background = std::make_shared<TitleSceneBackGround>();
	background->Init();
	m_objList.push_back(background);
	STAGEMANAGER.LoadRoom("Box");

	//スクロールするかどうか
	INFO.SetScrollFlg(false);
}
