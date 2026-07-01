#include "StageSelectSceneUi.h"
#include"../../../Common/CommonAPI.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Common/Input/Input.h"

#include"../../../Object/Ui/BaseButton/BaseButton.h"
#include"../UiBase.h"
#include"EnterStart/EnterStart.h"

#include"../../Num/Num.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
#include"MaxCoinFrame/MaxCoinFrame.h"

void StageSelectSceneUi::Init()
{
	//ステージセレクト
	std::shared_ptr<UiBase> stageselect = std::make_shared<UiBase>();
	stageselect->SetAsset("Asset/Textures/StageSelectScene/StageSelect/StageSelect.png");
	stageselect->SetPos({ 0,200,0 });
	SceneManager::Instance().AddObject(stageselect);

	//SelectArow
	std::shared_ptr<UiBase> selectarow = std::make_shared<UiBase>();
	selectarow->SetAsset("Asset/Textures/StageSelectScene/SelectArow/SelectArow.png");
	selectarow->SetPos({ 0,100,0 });
	selectarow->SetSize({ 0.65f,0.7f,0 });
	SceneManager::Instance().AddObject(selectarow);

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
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Stage1);
		});
	m_buttons[(int)StageSelectButton::Stage2]->ButtonLoad("Two", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Stage2);
		});
	m_buttons[(int)StageSelectButton::Stage3]->ButtonLoad("Three", []()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Stage3);
		});
	
	for (auto& button : m_buttons)
	{
		//オブジェクトリストにセット
		SceneManager::Instance().AddObject(button);
	}

	//EnterStart
	std::shared_ptr<EnterStart> enterstart = std::make_shared<EnterStart>();
	enterstart->Init();
	enterstart->SetAsset("StageSelectScene/EnterStart/EnterStart");
	enterstart->SetPos({ 200,-200,0 });
	enterstart->SetSize(0.8f);
	SceneManager::Instance().AddObject(enterstart);

	//最大コイン取得数
	std::shared_ptr<MaxCoinFrame> maxcoin = std::make_shared<MaxCoinFrame>();
	maxcoin->Init();
	SceneManager::Instance().AddObject(maxcoin);
}


void StageSelectSceneUi::Update()
{
	//選択ボタン制御
	SelectButtonControll();

	m_buttons[(int)m_selectbutton]->SelectUpdate();

	if (Inp.GetUserKeyDown(UserKeyType::DecisionKey))
	{
		KdAudioManager::Instance().Play("Asset/Sounds/SE/SceneChangeSE/SceneChangeSE.wav", false);

		m_buttons[(int)m_selectbutton]->Action();
	}
}

void StageSelectSceneUi::SelectButtonControll()
{
	if (Inp.GetUserKeyDown(UserKeyType::Right))
	{
		KdAudioManager::Instance().Play("Asset/Sounds/SE/SelectStageChangeSE/SelectStageChangeSE.wav");
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
		KdAudioManager::Instance().Play("Asset/Sounds/SE/SelectStageChangeSE/SelectStageChangeSE.wav");

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

