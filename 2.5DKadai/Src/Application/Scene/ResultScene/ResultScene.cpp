#include "ResultScene.h"
#include "../SceneManager.h"
#include"../../Object/BackGround/ResultSceneBackGround/ResultSceneBackGround.h"
#include"../../Manager/StageManager/StageManager.h"
#include"../../Common/Info/Info.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Ui/ResultSceneUi/ResultSceneUi.h"
#include"../../Common/Input/Input.h"
#include"../../Manager/ScoreManager/ScoreManager.h"
void ResultScene::Event()
{
	if (Inp.GetUserKeyDown(UserKeyType::DecisionKey))
	{
		if (m_resultsceneui->IsSkipThisFrame())
		{
			KdAudioManager::Instance().Play("Asset/Sounds/SE/SceneChangeSE/SceneChangeSE.wav", false);

			SceneManager::Instance().SetNextScene
			(
				SceneManager::SceneType::StageSelect
			);
		}
	}

	if (m_resultsceneui)
	{
		m_resultsceneui->Update();
	}
}

void ResultScene::Init()
{
	////平行光（ディレクショナルライト）								 　↓光方向　　↓色
	//KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1 }, { 1,1,1 });
	////環境光（アンビエントライト）										 　↓RGBA
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.1f,0.1f,0.1f,1 });

	//カメラ
	m_camera = std::make_unique<KdCamera>();

	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);

	//背景
	std::shared_ptr<ResultSceneBackGround> background = std::make_shared<ResultSceneBackGround>();
	background->Init();
	m_objList.push_back(background);

	//UI
	m_resultsceneui = std::make_shared<ResultSceneUi>();
	m_resultsceneui->Init();

	//プレイヤー
	//ゴールしていたらプレイヤー生成
	if (INFO.GetGoalFlg())
	{
		std::shared_ptr<Player> player = std::make_shared<Player>();
		player->Init();
		m_objList.push_back(player);
	}
	else
	{
		//プレイヤー
		std::shared_ptr<Player> splayer = std::make_shared<Player>();
		splayer->Init();
		//当たり判定のみ
		splayer->SetShadowFlg();
		m_objList.push_back(splayer);
	}

	//ステージ１をロード
	STAGEMANAGER.StageLoad("Result");

	INFO.SetScrollFlg(true);
	INFO.SetScrollSpeed(0.15f);

	Stage stage = Stage::None;

	if (INFO.GetStage() == "1")
	{
		stage = Stage::Stage1;
	}
	if (INFO.GetStage() == "2")
	{
		stage = Stage::Stage2;
	}
	if (INFO.GetStage() == "3")
	{
		stage = Stage::Stage3;
	}
	SCOREMANAGER.SetMaxCoin(stage);

	SCOREMANAGER.Save();
}
