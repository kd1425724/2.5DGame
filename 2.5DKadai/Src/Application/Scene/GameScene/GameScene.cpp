#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Common/Info/Info.h"
#include"../../Object/Ground/GameGround/GameGround.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Bat/Bat.h"
#include"../../Editor/Editor.h"
#include"../../Manager/StageManager/StageManager.h"
#include"../../Common/Input/Input.h"
#include"../../Object/BackGround/GameSceneBackGround/GameSceneBackGround.h"

void GameScene::Event()
{
	if (Inp.GetUserKeyDown(UserKeyType::DecisionKey))
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::StageSelect);
	}


	//エディターがカメラの主導権を持っているなら処理しない
	if (EDITOR.IsEditorCameraMode())return;
	
	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ};
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);

	m_player = std::make_shared<Player>();
	m_player->Init();
	m_objList.push_back(m_player);

	std::shared_ptr<GameSceneBackGround> background = std::make_shared<GameSceneBackGround>();
	background->Init();
	m_objList.push_back(background);

	//ステージ１をロード
	STAGEMANAGER.StageLoad("1");

	INFO.SetScrollFlg(true);
}