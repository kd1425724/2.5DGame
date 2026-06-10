#include "RoomExit.h"
#include"../../../Manager/StageManager/StageManager.h"
void RoomExit::Init()
{

}

void RoomExit::OnHit(KdGameObject* _other)
{
	//プレイヤーと当たった時
	if (_other->GetObjectTag() == ObjectTag::Player)
	{
		//部屋更新
		STAGEMANAGER.ChangeRoom();
	}
}
