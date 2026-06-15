#include "ResultScene.h"
#include "../SceneManager.h"
#include"../../Object/BackGround/TitleSceneBackGround/TitleSceneBackGround.h"
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

	
}

void ResultScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);

	//背景
	std::shared_ptr<TitleSceneBackGround> background = std::make_shared<TitleSceneBackGround>();
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
}
