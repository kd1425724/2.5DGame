#pragma once

class BaseButton;
class Num;

class StageSelectSceneUi
{
public:
	StageSelectSceneUi() { }
	~StageSelectSceneUi(){}

	void Init();
	void Update();



	void SelectButtonControll();

private:
	enum class StageSelectNumType
	{
		Coin,
		//Score,
		NumDrawNum
	};

	std::vector<std::shared_ptr<Num>> m_nums;

	enum class StageSelectButton
	{
		Stage1,
		Stage3,
		Stage2,
		ButtonNum
	};
	StageSelectButton m_selectbutton = StageSelectButton::Stage1;

	std::vector<std::shared_ptr<BaseButton>> m_buttons;
	
};
