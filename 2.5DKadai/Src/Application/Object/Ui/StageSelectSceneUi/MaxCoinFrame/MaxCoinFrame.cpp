#include "MaxCoinFrame.h"

#include "../../../../Manager/ScoreManager/ScoreManager.h"

#include"../../../Num/Num.h"

void MaxCoinFrame::Init()
{
	for (int i = 0; i < NumNum; i++)
	{
		m_num[i] = std::make_shared<Num>();
	}

	Math::Vector3 pos(-260, -122, 0);   // Stage1の数字位置
	Math::Vector3 scale(0.45f, 0.6f, 1);
	for (int i = 0; i < NumNum; i++)
	{
		m_num[i]->SetNumInfo(
			SCOREMANAGER.GetMaxCoin((Stage)(i + 1)),
			pos + Math::Vector3(0, -i * 67, 0),
			scale,
			{ 0.9f,0.9f,0,1.0f },
			false,
			3);
	}

	//フレーム
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/StageSelectScene/MaxCoinFrame/MaxCoinFrame.png");

	SetPos(Math::Vector3(-400, -200, 0));
	SetSize(0.25f);
	MatrixUpdate();
}

void MaxCoinFrame::Update()
{
	Math::Vector3 pos(-260,-122, 0);   // Stage1の数字位置
	Math::Vector3 scale(0.45f, 0.6f, 1);
	for (int i = 0; i < NumNum; i++)
	{
		m_num[i]->SetNumInfo(
			SCOREMANAGER.GetMaxCoin((Stage)(i)),
			pos+Math::Vector3(0,-i*67,0),
			scale,
			{0.9f,0.9f,0,1.0f},
			false,
			3);
	}
}

void MaxCoinFrame::DrawSprite()
{
	if (!m_tex)return;

	// 背景画像
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);

	Math::Color color = { 1,1,1,0.7f };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, nullptr, &color);
	
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);

	// 数字
	for (int i = 0; i < NumNum; i++)
	{
		m_num[i]->DrawSprite();
	}

	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);

}