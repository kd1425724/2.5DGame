#include "Slime.h"

void Slime::Release()
{}

void Slime::Init()
{
	m_pos = { 0,0,0 };

	m_statepattern = EnemyStatePattern::Loop;

	m_slimepattern = SlimePattern::Stop;
}

void Slime::Update()
{
	switch (m_statepattern)
	{
	case EnemyBase::EnemyStatePattern::Start:
		break;
	case EnemyBase::EnemyStatePattern::Loop:
		switch (m_slimepattern)
		{
		case Slime::SlimePattern::Stop:
			StopUpdate();
			break;
		case Slime::SlimePattern::Jump:
			JumpUpdate();
			break;
		default:
			break;
		}
		break;
	case EnemyBase::EnemyStatePattern::Death:
		break;
	default:
		break;
	}

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = mtrans;
}

void Slime::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Slime::StopInit()
{
	m_slimepattern = SlimePattern::Stop;
	m_stoptime = StopTime;
}

void Slime::StopUpdate()
{
	//UVRectControl(StopTime)
}

void Slime::JumpInit()
{}

void Slime::JumpUpdate()
{}

