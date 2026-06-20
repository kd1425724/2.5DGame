#include "OperationsUi.h"

void OperationsUi::Init()
{
	SetName("OperationUi");

	SetAsset("Asset/Textures/GameScene/Ui/Operations/Operations.png");

	m_alpha = 1.0f;
	m_cnt = 0;
	m_drawFlg = true;
}

void OperationsUi::Update()
{
	if (!m_drawFlg) return;

	m_cnt++;

	//10秒後からフェードアウト
	if (m_cnt > 60)
	{
		m_alpha -= 0.01f;

		if (m_alpha <= 0)
		{
			m_alpha = 0;
			m_drawFlg = false;
		}
	}
}

void OperationsUi::DrawSprite()
{
	if (!m_drawFlg) return;

	Math::Color color(1, 1, 1, m_alpha);
	if (!m_tex)return;


	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex,0,0,nullptr,&color);

	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}