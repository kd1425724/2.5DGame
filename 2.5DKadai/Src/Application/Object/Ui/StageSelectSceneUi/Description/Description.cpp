#include "Description.h"
#include"../Button/Button.h"
void StageDescription::Init()
{
	for (auto poly : m_descriptionpoly)
	{
		poly = std::make_shared<KdSquarePolygon>();
	}

	m_descriptionpoly[(int)StageSelectButtonInfo::Stage1]->SetMaterial("Asset/Textures/StageSelectScene/Description/Description1.png");

	Math::Vector3 pos = { 0,0,0 };

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(pos);
	m_mWorld = mtrans;
}

void StageDescription::DrawSprite()
{
	int buttoninfo = 0;

	if (auto button = m_button.lock())
	{
		buttoninfo = button->GetButtonInfo();
	}

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_descriptionpoly[buttoninfo], m_mWorld);
}

