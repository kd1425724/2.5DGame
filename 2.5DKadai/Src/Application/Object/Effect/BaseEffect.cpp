#include "BaseEffect.h"
#include"../../Common/Info/Info.h"

Math::Matrix BaseEffect::Scroll()
{
	m_pos.x -= INFO.GetScrollSpeed();

	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	return mtrans;
}
