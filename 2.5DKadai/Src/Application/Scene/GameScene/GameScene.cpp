#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/Ground/GameGround/GameGround.h"
#include"../../Object/Player/Player.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	
	//原点
	Math::Matrix mplayermat = Math::Matrix::CreateTranslation(m_player->GetPos());

	Math::Vector3 camerapos = { 0,0,-10 };
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(camerapos);
	//Math::Matrix mrot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(30));
	static Math::Matrix mrot2 = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));
	//mrot2 *= Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(2.1f));
	Math::Matrix mat = mtrans * mrot2 * mplayermat;

	m_camera->SetCameraMatrix(mat);
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();

	//地面
	std::shared_ptr<GameGround> ground = std::make_shared<GameGround>();
	ground->Init();
	m_objList.push_back(ground);

	//プレイヤー
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_objList.push_back(m_player);
}
