#include "TitleLogo.h"

void TitleLogo::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/");

	//行列読み込み
	Math::Matrix mscale = Math::Matrix::CreateScale(1);
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(0,0,0);
	m_mWorld = mscale * mtrans;
}
