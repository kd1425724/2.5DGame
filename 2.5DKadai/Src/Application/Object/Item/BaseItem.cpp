#include "BaseItem.h"
#include"../../Common/Info/Info.h"
std::shared_ptr<KdModelData> BaseItem::s_model;

void BaseItem::Update()
{
	Scroll();

	MatrixUpdate();
}