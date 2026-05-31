#include "CommonAsset.h"

CommonAsset::CommonAsset()
{
	m_whitebacktex = std::make_shared<KdTexture>();
	m_whitebacktex->Load("Asset/Textures/Common/Feed/WhiteBack.png");

	//数字
	m_numpoly = std::make_shared<KdSquarePolygon>();
	m_numpoly->SetMaterial("Asset/Textures/Common/Num/Num.png");
	m_numpoly->SetSplit(m_numrect.x, m_numrect.y);	//分割
}

CommonAsset::~CommonAsset()
{

}
