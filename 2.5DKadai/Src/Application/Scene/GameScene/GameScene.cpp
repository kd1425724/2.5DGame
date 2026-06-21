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
#include"../../Object/Ui/GameSceneUi/GameSceneUi.h"
#include"../../Common/Feed/Feed.h"
#include"../../Object/CountDown/CountDown.h"

void GameScene::Event()
{
	//ゴールしたら
	if (INFO.GetGoalFlg())
	{
		m_goalcnt++;

		//0.5秒後にリザルトへ(60fps想定)
		if (m_goalcnt > 60)
		{
			//スクロール停止
			INFO.SetScrollFlg(false);
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		}

		return;
	}
	//プレイヤー死亡時即リザルトへ
	if (m_player.expired())
	{
		INFO.SetScrollFlg(false);
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		return;
	}
	switch (m_gamepattern)
	{
	case GameScene::GamePattern::Stop:
		//フェードインが終了したら
		if (FEED.GetFeedState() == NoFeed)
		{
			m_gamepattern = GamePattern::CountDown;
		}
		break;
	case GameScene::GamePattern::CountDown:
		//カウントダウン処理
		//GO!!が表示されたら開始
		//カウントダウン処理をしている側で変更
		if (m_countdown)
		{
			if (m_countdown->IsFinish())
			{
				m_gamepattern = GamePattern::Start;
			}
		}
		break;
	case GameScene::GamePattern::Start:
		//開始(一度だけ通る)
		INFO.SetScrollFlg(true);
		INFO.SetScrollSpeed(INFO.GetDefaultScrollSpeed());
		m_gamepattern = GamePattern::Game;
		break;
	case GameScene::GamePattern::Game:
		//特に何もしなくていい
		break;
	default:
		break;
	}
	

	if (m_gamesceneui)
	{
		m_gamesceneui->Update();
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

	m_goalcnt = 0;
	INFO.SetGoalFlg(false);
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	Math::Vector3 camerapos = { 0,0,INFO.DefaultCameraPosZ };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	Math::Matrix mat = mtrans;

	m_camera->SetCameraMatrix(mat);

	auto player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);
	m_player = player;

	std::shared_ptr<GameSceneBackGround> background = std::make_shared<GameSceneBackGround>();
	background->Init();
	m_objList.push_back(background);

	//UI
	m_gamesceneui = std::make_shared<GameSceneUi>();
	m_gamesceneui->Init();

	//ステージをロード
	STAGEMANAGER.StageLoad(m_stagepath);

	m_gamepattern = GamePattern::Stop;

	INFO.SetScrollFlg(false);

	//カウントダウン処理
	m_countdown = std::make_shared<CountDown>();
	m_countdown->Init();
	m_objList.push_back(m_countdown);
}