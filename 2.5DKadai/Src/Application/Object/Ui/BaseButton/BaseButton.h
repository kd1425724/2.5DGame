#pragma once
#include"../UiBase.h"

class BaseButton:public UiBase
{
public:
	BaseButton(){}
	~BaseButton()override{}

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void DrawLit()override;

	void SelectUpdate();

	void ButtonLoad(const std::string& _filename,std::function<void()> _action);

	void Action();

	void SetPos(const Math::Vector3& pos)override
	{
		m_basepos = pos;
		m_pos = m_basepos;
		MatrixUpdate();
	}

protected:

	std::shared_ptr<KdModelData> m_model;

	std::function<void()> m_action = nullptr;

	bool m_selectflg = false;

private:

	Math::Vector3 m_basepos = {};

	float m_time=0;

	float m_speed = 0.1f;

};

