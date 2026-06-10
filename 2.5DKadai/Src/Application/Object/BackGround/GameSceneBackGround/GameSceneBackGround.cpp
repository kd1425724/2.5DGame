#include "GameSceneBackGround.h"

void GameSceneBackGround::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/GameScene/BackGround/GameSceneBackGround.png");
	
	m_polygon->SetScale({ 100,40 });

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(0, 0, 20);
	m_mWorld = mtrans;
}

void GameSceneBackGround::Update()
{}

void GameSceneBackGround::DrawUnLit()
{
	Math::Color color = { 0.7f,0.7f,0.7f,1.0f };
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon,m_mWorld,color);
}
