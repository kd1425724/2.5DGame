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
	Math::Vector3 coinpos = { 560,290,0 };
	Math::Vector3 scale = { 2,2,2 };
	m_nums[(int)GameNumType::Coin]->SetNumInfo
	(
		SCOREMANAGER.GetCoin(),
		coinpos,
		scale
	);

}
