#pragma once

class BaseButton;

class StageSelectSceneUi
{
public:
	StageSelectSceneUi() { }
	~StageSelectSceneUi(){}

	void Init();
	void Update();



	void SelectButtonControll();

private:

	enum class StageSelectButton
	{
		Stage1,
		Stage2,
		Stage3,
		ButtonNum
	};
	StageSelectButton m_selectbutton = StageSelectButton::Stage1;

	std::vector<std::shared_ptr<BaseButton>> m_buttons;
	
};
