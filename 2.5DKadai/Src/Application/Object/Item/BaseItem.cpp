#include "BaseItem.h"
#include"../../Common/Info/Info.h"
void BaseItem::Update()
{
	m_pos.x -= INFO.GetScrollSpeed();

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = mtrans;
}

Math::Matrix BaseItem::Scroll()
{
	m_pos.x -= INFO.GetScrollSpeed();

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	return mtrans;
}
