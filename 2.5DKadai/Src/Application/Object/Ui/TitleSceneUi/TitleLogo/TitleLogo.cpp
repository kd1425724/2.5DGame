#include "TitleLogo.h"

void TitleLogo::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/TitleScene/Ui/TitleLogo/CubeRun.png");
}

void TitleLogo::Update()
{
}

void TitleLogo::DrawSprite()
{
	if (!m_tex)return;

	// 縁の太さ
	const int outline = 10;

	// 元の座標
	Math::Vector3 pos = m_pos;

	Math::Color color = { 0,0,0,1 };
	
	for (int x = -outline; x <= outline; x++)
	{
		for (int y = -outline; y <= outline; y++)
		{
			if (x == 0 && y == 0) continue;

			Math::Matrix mat =m_mWorld*
				Math::Matrix::CreateTranslation(x,y,0);

			KdShaderManager::Instance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0,nullptr,&color);
		}
	}

	// 本体
	color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, nullptr, &color);

	// 戻す
	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

