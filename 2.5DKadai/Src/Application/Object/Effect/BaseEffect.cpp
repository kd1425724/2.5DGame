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
	if ((m_flag & eScroll))
	{
		m_pos.x -= INFO.GetScrollSpeed();
	}

	if (m_anim.empty())
	{
		SetExpired();
		return;
	}


	// ホーミング
	if (m_flag & eHoming)
	{
		if (!m_target.expired())
		{
			auto targrt = m_target.lock();

			m_targetPos = targrt->GetPos();
		}

		Math::Vector3 dir = m_targetPos - m_pos;

		float len = dir.Length();

		if (len > m_homingSpeed)
		{
			dir /= len;
			m_pos += dir * m_homingSpeed;
		}
		else
		{
			m_pos = m_targetPos;
			SetExpired();   // 到着したら消える
		}
	}

	m_animCnt += m_animSpeed;

	if ((int)m_animCnt >= m_anim.size())
	{
		//ループ
		if (m_flag & eLoop)
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
	if (!(m_flag & eBright)) return;

	if (!m_polygon) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void BaseEffect::DrawEffect()
{
	if (m_flag & eBright) return;

	if (!m_polygon) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

