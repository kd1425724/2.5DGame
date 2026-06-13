#include "StageSelectSceneUi.h"
#include"../../../Common/CommonAPI.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Common/Input/Input.h"

#include"Description/Description.h"
#include"Button/Button.h"
#include"../../../Object/Ui/BaseButton/BaseButton.h"

#include"../../Num/Num.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"

void StageSelectSceneUi::Init()
{
	m_nums.resize((int)StageSelectNumType::NumDrawNum);

	for (auto& num : m_nums)
	{
		num = std::make_shared<Num>();
		SceneManager::Instance().AddObject(num);
	}
	//ボタン
	m_buttons.push_back(std::make_shared<BaseButton>());
	m_buttons.push_back(std::make_shared<BaseButton>());
	m_buttons.push_back(std::make_shared<BaseButton>());
	int i = 0;
	for (auto& button : m_buttons)
	{
		//先に全部初期化
		button->Init();
		button->SetPos(Math::Vector3(-3 + (i * 3), 0, 0));

		i++;
	}
	//ボタンの情報セット
	m_buttons[(int)StageSelectButton::Stage1]->ButtonLoad("Stage1", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		});
	m_buttons[(int)StageSelectButton::Stage2]->ButtonLoad("Stage2", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		});
	m_buttons[(int)StageSelectButton::Stage3]->ButtonLoad("Stage3", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		});
	
	for (auto& button : m_buttons)
	{
		//オブジェクトリストにセット
		SceneManager::Instance().AddObject(button);
	}
}


void StageSelectSceneUi::Update()
{
	//コイン
	Math::Vector3 coinpos = { 600,300,0 };
	m_nums[(int)StageSelectNumType::Coin]->SetNumInfo
	(
		1003,
		coinpos
	);

	m_buttons[(int)m_selectbutton]->SelectUpdate();

	if (Inp.GetUserKeyDown(UserKeyType::DecisionKey))
	{
		m_buttons[(int)m_selectbutton]->Action();
	}
}

void StageSelectSceneUi::SelectButtonControll()
{}

