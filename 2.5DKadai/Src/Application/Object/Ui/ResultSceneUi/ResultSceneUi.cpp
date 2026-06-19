#include "ResultSceneUi.h"
#include"../CommonUi/BlackBack/BlackBack.h"
#include"../../../Scene/SceneManager.h"
#include"../../Item/Coin/Coin.h"
#include"../../Num/Num.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
#include"Rank/Rank.h"
#include"../../../Common/Info/Info.h"
#include"Result/Result.h"

void ResultSceneUi::Init()
{
	std::shared_ptr<BlackBack> blackback = std::make_shared<BlackBack>();
	blackback->Init();
	SceneManager::Instance().AddObject(blackback);

	m_nums.resize((int)ResultNumType::NumDrawNum);

	for (auto& num : m_nums)
	{
		num = std::make_shared<Num>();
	}

	//コイン
	UINT coin = SCOREMANAGER.GetCoin();
	Math::Vector3 coinpos = { 100,0,0 };
	Math::Vector3 scale = { 0.5,0.7,1 };
	m_nums[(int)ResultNumType::Coin]->SetNumInfo
	(
		coin,
		coinpos,
		scale
	);

	for (auto& num : m_nums)
	{
		SceneManager::Instance().AddObject(num);
	}

	//コイン
	std::shared_ptr<Coin> scorecoin = std::make_shared<Coin>();
	scorecoin->Init();
	scorecoin->SetPos({ -1.0f,0.6f,-2.0 });
	scorecoin->SetSize(0.8f);
	scorecoin->SetHitFlg(false);
	SceneManager::Instance().AddObject(scorecoin);


	//ランク
	std::shared_ptr<Rank> rank = std::make_shared<Rank>();
	rank->Init();
	rank->SetPos({ 0,-100,0 });
	SceneManager::Instance().AddObject(rank);

	//リザルト
	std::shared_ptr<Result> result = std::make_shared<Result>();
	result->Init();
	result->SetPos({0,200,0});
	SceneManager::Instance().AddObject(result);
}

void ResultSceneUi::Update()
{
	//コイン
	UINT coin = SCOREMANAGER.GetCoin();
	Math::Vector3 coinpos = { 100,50,0 };
	Math::Vector3 scale = { 0.5,0.7,1 };
	m_nums[(int)ResultNumType::Coin]->SetNumInfo
	(
		coin,
		coinpos,
		scale
	);
}
