#include "CountDown.h"
#include"../Num/Num.h"
void CountDown::Init()
{
	SetName("CountDown");

	m_goTex = std::make_shared<KdTexture>();
	m_goTex->Load("Asset/Textures/GameScene/CountDown/GO.png");

	m_num = std::make_shared<Num>();

	m_scale = { 3,3,1 };

	MatrixUpdate();
}

void CountDown::Update()
{
	if (m_pattern == End) return;

	m_count++;

	// GOだけ短め
	if (m_pattern == Go)
	{
		m_changeTime = 30;
	}
	else
	{
		m_changeTime = 40;
	}

	if (m_count >= m_changeTime)
	{
		m_count = 0;

		m_pattern = (CountPattern)((int)m_pattern + 1);

		if (m_pattern > End)
		{
			m_pattern = End;
		}
	}
}

void CountDown::DrawSprite()
{
	if (m_pattern == End) return;

	// 3,2,1
	if (m_pattern <= One)
	{
		m_num->SetNumInfo(
			3 - (int)m_pattern,
			m_pos,
			m_scale);

		m_num->DrawSprite();
	}
	// GO!!
	else if (m_pattern == Go)
	{
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_goTex,
			0,
			0);

		KdShaderManager::Instance().m_spriteShader.SetMatrix(
			Math::Matrix::Identity);
	}
}