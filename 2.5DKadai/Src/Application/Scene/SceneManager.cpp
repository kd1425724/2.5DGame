#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include"StageSelectScene/StageSelectScene.h"
#include "GameScene/GameScene.h"
#include"ResultScene/ResultScene.h"

#include"../Common/CommonAPI.h"
#include"../Common/Input/Input.h"
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
	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::StageSelect:
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<StageSelectScene>();
		break;
	case SceneType::Game:
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<GameScene>();
		break;
	case SceneType::Result:
		COMMONAPI.Clear();
		m_currentScene = std::make_shared<ResultScene>();
		break;
	}

	// Sceneが確定していない状況でInit()でObjectListにObjectを保持しがちなので
	// コントラクタでのInit()を禁止します！！！
	m_currentScene->Init();

	// 現在のシーン情報を更新
	m_currentSceneType = _sceneType;
}
