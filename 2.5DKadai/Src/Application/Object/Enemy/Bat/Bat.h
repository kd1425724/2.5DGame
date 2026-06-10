#pragma once
#include"../EnemyBase.h"

class Bat:public EnemyBase
{
public:
	Bat(){}
	~Bat(){}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	enum class BatAnimType 
	{
		Fly,	//飛行
		AnimNum
	};
	BatAnimType m_animtype = BatAnimType::Fly;

	void UVRectControl(int _animtype, std::function<void()> _action = nullptr)override;

	//サイズ
	Math::Vector3 m_scale = {};
};
