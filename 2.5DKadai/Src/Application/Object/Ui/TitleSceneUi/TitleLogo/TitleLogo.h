#pragma once
#include"../../UiBase.h"

class TitleLogo:public UiBase
{
public:
	TitleLogo(){}
	~TitleLogo()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

private:

};
