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
	//ボタン
	m_buttons.resize((int)StageSelectButton::ButtonNum);
	int i = 0;
	constexpr float interval = 4.0f;
	for (auto& button : m_buttons)
	{
		button=std::make_shared<BaseButton>();
		//先に全部初期化
		button->Init();
		
		button->SetPos(Math::Vector3(
			-(interval * ((int)StageSelectButton::ButtonNum - 1) / 2.0f)
			+ i * interval,
			0,
			0));
		i++;
	}
	//ボタンの情報セット
	m_buttons[(int)StageSelectButton::Stage1]->ButtonLoad("One", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		});
	m_buttons[(int)StageSelectButton::Stage2]->ButtonLoad("Two", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		});
	m_buttons[(int)StageSelectButton::Stage3]->ButtonLoad("Three", []()
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
	//選択ボタン制御
	SelectButtonControll();

	m_buttons[(int)m_selectbutton]->SelectUpdate();

	if (Inp.GetUserKeyDown(UserKeyType::DecisionKey))
	{
		m_buttons[(int)m_selectbutton]->Action();
	}
}

void StageSelectSceneUi::SelectButtonControll()
{
	if (Inp.GetUserKeyDown(UserKeyType::Right))
	{
		if (m_selectbutton == StageSelectButton::Stage3)
		{
			m_selectbutton = StageSelectButton::Stage1;
		}
		else
		{
			m_selectbutton =(StageSelectButton)((int)m_selectbutton + 1);
		}
	}

	if (Inp.GetUserKeyDown(UserKeyType::Left))
	{
		if (m_selectbutton == StageSelectButton::Stage1)
		{
			m_selectbutton =
				(StageSelectButton)((int)StageSelectButton::ButtonNum - 1);
		}
		else
		{
			m_selectbutton =
				(StageSelectButton)((int)m_selectbutton - 1);
		}
	}
}

