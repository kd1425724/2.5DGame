#pragma once

class Num;

class ResultSceneUi
{
public:
	ResultSceneUi(){}
	~ResultSceneUi(){}

	void Init();
	void Update();

private:

	enum class ResultNumType
	{
		Coin,
		NumDrawNum
	};

	std::vector<std::shared_ptr<Num>> m_nums;
};
