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

protected:

	std::shared_ptr<KdModelData> m_model;

	std::function<void()> m_action = nullptr;

	bool m_selectflg = false;

private:

};

