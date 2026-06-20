#include "BaseEvent.h"
#include"../../Common/Info/Info.h"

void BaseEvent::Update()
{
	m_pos.x -= INFO.GetScrollSpeed();

	MatrixUpdate();
}

void BaseEvent::PreUpdate()
{
	/*if (m_pDebugWire)
	{
		m_pDebugWire->AddDebugBox(m_mWorld, {0.5,1,0.5f}, {}, false, kRedColor);
	}*/
}
