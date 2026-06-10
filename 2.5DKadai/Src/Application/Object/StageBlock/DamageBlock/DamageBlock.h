#pragma once
#include"../BaseStageBlock.h"

class DamageBlock:public BaseStageBlock
{
public:
	DamageBlock(){}
	~DamageBlock()override{}

	void Init()override;

	//ダメージ判定
	ObjectTag GetObjectTag()override { return ObjectTag::Damage; }
private:

};