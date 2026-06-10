#include "Goal.h"

void Goal::OnHit(KdGameObject* _other)
{
	//プレイヤーと当たったら
	if (_other->GetObjectTag() == ObjectTag::Goal)
	{
		//サウンド（未実装）

		//ゴール処理

		//消滅
		m_isExpired = true;
	}
}
