#include "EnemyBase.h"

void EnemyBase::UVRectControl(int _animtime, std::vector<int> _animid,int _animcnt, std::function<void()> _action)
{
	m_action = nullptr;

	m_animtime = _animtime;

	m_animid = _animid;

	m_animmax = m_animid.size() - 1;

	m_loopmax = _animcnt; 
	m_animcnt = m_loopmax;
	

	
	if (_action)
	{
		m_action = _action;
	}
}

void EnemyBase::UVRectControlUpdate()
{
	float oneanimtime = (float)m_animtime / m_loopmax;
	m_anim += m_animmax / oneanimtime;

	if (m_anim >= m_animmax)
	{
		m_animcnt--;
	
		//animcntが０になるまでループ
		if (m_animcnt <= 0)
		{
			if (m_action)
			{
				m_action();
				return;
			}
			else
			{
				m_anim = 0;
				return;
			}
		}

		m_anim = 0;
		
	}

	m_polygon->SetUVRect(m_animid[(int)m_anim]);
}
