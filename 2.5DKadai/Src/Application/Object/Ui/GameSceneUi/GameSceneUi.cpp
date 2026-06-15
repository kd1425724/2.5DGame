#include "GameSceneUi.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Manager/ScoreManager/ScoreManager.h"
#include"../../Num/Num.h"
void GameSceneUi::Init()
{
	m_nums.resize((int)GameNumType::NumDrawNum);

	for (auto& num : m_nums)
	{
		num = std::make_shared<Num>();
		SceneManager::Instance().AddObject(num);
	}
}

void GameSceneUi::Update()
{
	//コイン
	Math::Vector3 coinpos = { 600,300,0 };
	m_nums[(int)GameNumType::Coin]->SetNumInfo
	(
		SCOREMANAGER.GetCoin(),
		coinpos
	);

}
