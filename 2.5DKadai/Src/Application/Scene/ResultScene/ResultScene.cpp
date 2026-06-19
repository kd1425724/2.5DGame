#include "ResultScene.h"
#include "../SceneManager.h"
#include"../../Object/BackGround/ResultSceneBackGround/ResultSceneBackGround.h"
#include"../../Manager/StageManager/StageManager.h"
#include"../../Common/Info/Info.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Ui/ResultSceneUi/ResultSceneUi.h"
void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::StageSelect
		);
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

	//Fog（霧）														↓距離　↓高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	//距離フォグの設定													↓色	  ↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.05f);
	//高さフォグの設定													↓色  ↓上↓下↓距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0.8,0.8,0.8 }, -3, -8, 0);

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
}
