#include "GoalDisplay.h"
#include"../../Common/Info/Info.h"

void GoalDisplay::Init()
{
	SetName("GoalDisplay");

	m_goalTex = std::make_shared<KdTexture>();
	m_goalTex->Load("Asset/Textures/GameScene/Goal/Goal.png");

	m_scale = { 3,3,1 };

	m_isVisible = false;

	m_isFinish = false;

	MatrixUpdate();
}

void GoalDisplay::Update()
{
	// ゴールしたら表示開始
	if (!m_isVisible && INFO.GetGoalFlg())
	{
		m_isVisible = true;
		m_count = 0;
	}

	// 表示中のカウント
	if (m_isVisible && !m_isFinish)
	{
		m_count++;

		if (m_count >= DISPLAY_TIME)
		{
			m_isFinish = true;
		}
	}
}

void GoalDisplay::DrawSprite()
{
	// 表示中でなければ描画しない
	if (!m_isVisible || m_isFinish) return;

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	Math::Color color = { 1,1,0,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_goalTex, 0, 0, nullptr, &color);

	KdShaderManager::Instance().m_spriteShader.SetMatrix(
		Math::Matrix::Identity);
}
