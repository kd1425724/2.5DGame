#include "Goal.h"
#include"../../../Common/Info/Info.h"

void Goal::OnHit(KdGameObject* _other)
{
	//プレイヤーと当たったら
	if (_other->GetObjectTag() == ObjectTag::Goal)
	{
		//サウンド（未実装）

		//ゴール
		INFO.SetGoalFlg(true);

		//消滅
		m_isExpired = true;
	}
}
