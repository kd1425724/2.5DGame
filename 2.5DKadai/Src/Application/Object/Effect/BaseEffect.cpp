#include "BaseEffect.h"
#include"../../Common/Info/Info.h"

void BaseEffect::Init()
{
	//m_drawType = eDrawTypeBright;

	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial(m_assetName);

	m_polygon->SetSplit(m_splitX, m_splitY);

	if (!m_anim.empty())
	{
		m_polygon->SetUVRect(m_anim[0]);
	}

	MatrixUpdate();
}

void BaseEffect::Update()
{
	m_pos.x -= INFO.GetScrollSpeed();

	m_animCnt += m_animSpeed;

	if (m_anim.empty())
	{
		SetExpired();
		return;
	}

	if ((int)m_animCnt >= m_anim.size())
	{
		if (m_loop)
		{
			while ((int)m_animCnt >= m_anim.size())
			{
				m_animCnt -= (float)m_anim.size();
			}
		}
		else
		{
			SetExpired();
			return;
		}
	}
	int index = m_anim[(int)m_animCnt];

	m_polygon->SetUVRect(index);



	MatrixUpdate();
}

void BaseEffect::DrawBright()
{
	if (!m_polygon) return;

	
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);

	
}

void BaseEffect::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

