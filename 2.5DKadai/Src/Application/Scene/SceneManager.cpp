#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include"StageSelectScene/StageSelectScene.h"
#include "GameScene/GameScene.h"
#include"ResultScene/ResultScene.h"

#include"../Common/CommonAPI.h"
#include"../Common/Input/Input.h"
#include"../Common/Info/Info.h"
#include"../Common/Feed/Feed.h"

#include"../Editor/Editor.h"

#include"../Manager/ScoreManager/ScoreManager.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		//フェード処理
		FEED.FeedOutInit(30, [this]()
		{
			ChangeScene(m_nextSceneType);
			FEED.FeedInInit(30);
		});
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", GetObjList().size());

	FEED.Update();

	SCOREMANAGER.Update();

	if (FEED.GetFeedState() == FeedOut)return;

	//エディター中オブジェクトの更新可能かどうか
	if (EDITOR.IsEditMode() && !EDITOR.IsObjectUpdateMode())return;

	m_currentScene->Update();

	COMMONAPI.CreateButtonUpdate();


	//デバッグキー
	if (Inp.GetDebugKeyDown(DebugKeyType::PKey))
	{
		SetNextScene(SceneType::Title);
		return;
	}

	if (Inp.GetDebugKeyDown(DebugKeyType::ZEROKey))
	{
		INFO.SetGoalFlg(false);
		SetNextScene(SceneType::Result);
		return;
	}
	if (Inp.GetDebugKeyDown(DebugKeyType::NINEKey))
	{
		INFO.SetGoalFlg(true);
		SetNextScene(SceneType::Result);
		return;
	}
	if (Inp.GetDebugKeyDown(DebugKeyType::IKey))
	{
		SetNextScene(SceneType::Goal);
		return;
	}
}

void SceneManager::PostUpdate()
{
	//エディター中オブジェクトの更新可能かどうか
	if (EDITOR.IsEditMode() && !EDITOR.IsObjectUpdateMode())return;

	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();

	COMMONAPI.CreateButtonDrawSprite();

	//フェード処理（最後）
	FEED.DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

KdCamera* SceneManager::GetCamera()
{
	//カメラ取得
	return m_currentScene->GetCamera();
}

void SceneManager::Init()
{
	// 開始シーンに切り替え
	ChangeScene(m_currentSceneType);
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	//前のシーンを保存
	m_OldSceneType = m_currentSceneType;

	// 現在のシーン情報を更新
	m_currentSceneType = _sceneType;

	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/TitleBGM.wav", true);
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::StageSelect:
		//前のシーンがタイトル以外なら	
		if (m_OldSceneType != SceneType::Title)
		{
			KdAudioManager::Instance().StopAllSound();
			KdAudioManager::Instance().Play("Asset/Sounds/BGM/TitleBGM.wav", true);
		}
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<StageSelectScene>();
		break;
	case SceneType::Stage1:
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/GameBGM.wav", true);
		//スコアリセット
		SCOREMANAGER.ScoreReset();
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<GameScene>("1");
		INFO.SetStage("1");
		break;
	case SceneType::Stage2:
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/GameBGM.wav", true);
		//スコアリセット
		SCOREMANAGER.ScoreReset();
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<GameScene>("2");
		INFO.SetStage("2");
		break;
	case SceneType::Stage3:
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/GameBGM.wav", true);
		//スコアリセット
		SCOREMANAGER.ScoreReset();
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<GameScene>("3");
		INFO.SetStage("3");
		break;
	case SceneType::Result:
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/ResultBGM.wav", true);
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<ResultScene>();
		break;
	case SceneType::Goal:
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/GameBGM.wav", true);
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<GameScene>("Goal");
		break;
	}

	
	// Sceneが確定していない状況でInit()でObjectListにObjectを保持しがちなので
	// コントラクタでのInit()を禁止します！！！
	m_currentScene->Init();


}
