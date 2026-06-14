#pragma once

class EffectManager
{
public:

	struct EffectData
	{
		std::string assetName="";

		UINT splitX=1;
		UINT splitY=1;

		std::vector<int> anim = {};

		float animSpeed=0.2f;

		float scale = 1;

		bool loop=false;
	};

	void Init();

	void CreateEffect(
		const std::string& name,
		const Math::Vector3& pos);

private:

	std::unordered_map<
		std::string,
		EffectData
	> m_effectTable;

private:
	EffectManager() { Init(); };
	~EffectManager() {};

public:

	static EffectManager& Instance()
	{
		static EffectManager instance;

		return instance;
	}

};

#define EFFECT EffectManager::Instance()