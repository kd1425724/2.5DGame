#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/Ground/GameGround/GameGround.h"
#include"../../Object/Player/Player.h"

#include"../../Editor/Editor.h"


void GameScene::Event()
{



	//エディターがカメラの主導権を持っているなら処理しない
	if (EDITOR.IsEditorCameraMode())return;
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

	//プレイヤー
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_objList.push_back(m_player);
}

void GameScene::ChangeRoom(std::string nextFile, int nextId)
{
	//今の部屋削除
	EDITOR.UnLoadRoom(m_currentRoomId);

	//次の部屋生成
	EDITOR.LoadRoom(nextFile, nextId);

	//更新
	m_currentRoomId = nextId;
}
