#pragma once

class Num;
class Rank;

class ResultSceneUi
{
public:
	ResultSceneUi(){}
	~ResultSceneUi(){}

	void Init();
	void Update();

	bool IsSkipThisFrame() const;

private:

	enum class ResultNumType
	{
		Coin,
		NumDrawNum
	};

	std::vector<std::shared_ptr<Num>> m_nums;

	std::weak_ptr<Rank> m_rank;
};
