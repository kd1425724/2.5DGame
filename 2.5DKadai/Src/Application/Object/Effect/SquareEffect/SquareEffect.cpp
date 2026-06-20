#include"SquareEffect.h"
#include"../../../Common/Info/Info.h"

void SquareEffect::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial(KdAssets::Instance().m_textures.GetData("Asset/Textures/Effect/SquareEffect/SquareEffect.png"));
}

void SquareEffect::Update()
{
	m_pos += m_vel;

	//スクロール
	m_pos.x -= INFO.GetScrollSpeed();

	m_scale *= 0.95f;

	m_alpha -= 0.05f;

	m_life--;

	if (m_life <= 0)
	{
		SetExpired();
	}

	MatrixUpdate();
}

void SquareEffect::DrawEffect()
{
	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().
		m_StandardShader.DrawPolygon(*m_polygon,m_mWorld,color);
}

void SquareEffect::DrawBright()
{
	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().
		m_StandardShader.DrawPolygon(*m_polygon, m_mWorld,color);
}
