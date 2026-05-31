#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include"StageSelectScene/StageSelectScene.h"
#include "GameScene/GameScene.h"

#include"../Common/CommonAPI.h"
#include"../Common/Input/Input.h"
#include"../Common/Feed/Feed.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	FEED.Update();

	if (FEED.GetFeedState() == FeedOut)return;

	m_currentScene->Update();

	COMMONAPI.CreateButtonUpdate();
}

void SceneManager::PostUpdate()
{
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

void SceneManager::Init()
{
	m_currentScene = std::make_shared<TitleScene>();
	// 開始シーンに切り替え
	ChangeScene(m_currentSceneType);
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	/*FEED.FeedOutInit(30, [_sceneType,this]() 
		{*/
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
			}

			// 現在のシーン情報を更新
			m_currentSceneType = _sceneType;

		/*	FEED.FeedInInit(30);
		});*/
}
