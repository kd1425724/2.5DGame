#include "BaseEvent.h"
#include"../../Common/Info/Info.h"

void BaseEvent::Update()
{
	m_pos.x -= INFO.GetScrollSpeed();

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = mtrans;
}
