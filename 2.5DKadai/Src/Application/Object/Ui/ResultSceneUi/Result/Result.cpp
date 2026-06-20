#include "Result.h"
#include"../../../../Common/Info/Info.h"
void Result::Init()
{
	SetName("Result");

	bool flg = INFO.GetGoalFlg();
	m_result = Clear;

	if (flg)
	{
		m_result = Clear;
	}
	else	
	{ 
		m_result = GameOver;
	}
	m_clearTex = std::make_shared<KdTexture>();
	m_clearTex->Load("Asset/Textures/ResultScene/Result/Clear.png");

	m_gameOverTex = std::make_shared<KdTexture>();
	m_gameOverTex->Load("Asset/Textures/ResultScene/Result/GameOver.png");

	m_scale = { 1,1,1 };

	MatrixUpdate();
}

void Result::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	Math::Color color={1,1,0,1};

	switch (m_result)
	{
	case Clear:
		color = { 1,1,0,1 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_clearTex,
			0,
			0, nullptr, &color);

		break;

	case GameOver:
		color = { 1,0,0,1 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_gameOverTex,
			0,
			0,nullptr,&color);

		break;

	default:
		break;
	}

	KdShaderManager::Instance().m_spriteShader.SetMatrix(
		Math::Matrix::Identity);
}