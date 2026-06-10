#include "CommonAsset.h"

CommonAsset::CommonAsset()
{
	m_whitebacktex = std::make_shared<KdTexture>();
	m_whitebacktex->Load("Asset/Textures/Common/Feed/WhiteBack.png");

	//数字
	m_numtex = std::make_shared<KdTexture>();
	m_numtex->Load("Asset/Textures/Common/Num/Num.png");
}

CommonAsset::~CommonAsset()
{

}
