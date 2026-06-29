#include "GameSceneUi.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
#include"../../Num/Num.h"
#include"../../Item/Coin/Coin.h"
#include"OperationsUi/OperationsUi.h"
#include"../../GoalDisplay/GoalDisplay.h"

void GameSceneUi::Init()
{
	m_nums.resize((int)GameNumType::NumDrawNum);

	for (auto& num : m_nums)
	{
		num = std::make_shared<Num>();
	}

	//コイン
	Math::Vector3 coinpos = { -350,280,0 };
	Math::Vector3 scale = { 0.5,0.7,1 };
	m_nums[(int)GameNumType::Coin]->SetNumInfo
	(
		SCOREMANAGER.GetCoin(),
		coinpos,
		scale
	);

	for (auto& num: m_nums)
	{
		SceneManager::Instance().AddObject(num);
	}

	//コインオブジェクト
	std::shared_ptr<Coin> scorecoin = std::make_shared<Coin>();
	scorecoin->Init();
	scorecoin->SetPos({-6.9f,3.6f,-2});
	scorecoin->SetSize(0.8f);
	scorecoin->SetHitFlg(false);
	SceneManager::Instance().AddObject(scorecoin);

	Coin::SetTarget(scorecoin);

	std::shared_ptr<OperationsUi> operationsui = std::make_shared<OperationsUi>();
	operationsui->Init();
	operationsui->SetPos({ 320,200,0 });
	operationsui->SetSize(0.25);
	SceneManager::Instance().AddObject(operationsui);

	//Goal!!
	std::shared_ptr<GoalDisplay> goaldisplay = std::make_shared<GoalDisplay>();
	goaldisplay->Init();
	SceneManager::Instance().AddObject(goaldisplay);
}

void GameSceneUi::Update()
{
	//コイン
	UINT coin = SCOREMANAGER.GetCoin();
	Math::Vector3 coinpos = { -350,280,0 };
	Math::Vector3 scale = { 0.5,0.7,1 };
	m_nums[(int)GameNumType::Coin]->SetNumInfo
	(
		coin,
		coinpos,
		scale
	);
}
