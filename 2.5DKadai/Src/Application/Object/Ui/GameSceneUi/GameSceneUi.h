#pragma once

class Num;

class GameSceneUi
{
public:
	GameSceneUi(){}
	~GameSceneUi(){}

	void Init();
	void Update();
	

private:
	enum class GameNumType
	{
		Coin,
		NumDrawNum
	};

	std::vector<std::shared_ptr<Num>> m_nums;

};