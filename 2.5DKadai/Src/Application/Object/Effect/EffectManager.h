#pragma once

class BaseEffect;

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
	};

	void Init();

	void CreateEffect(
		const std::string& name,
		const Math::Vector3& pos,
		UINT flag = 0);

	void CreateEffectHoming(
		const std::string& name,
		const Math::Vector3& pos,
		const Math::Vector3& targetPos,
		UINT flag = 0,
		float homingspeed = 0.2f);

	void CreateEffectHoming(
		const std::string& name,
		const Math::Vector3& pos,
		const std::shared_ptr<KdGameObject>& targetObj,
		UINT flag = 0,
		float homingspeed = 0.2f);

private:

	std::unordered_map<
		std::string,
		EffectData
	> m_effectTable;

	std::shared_ptr<BaseEffect> CreateBaseEffect(
		const std::string& name,
		const Math::Vector3& pos,
		UINT flag);

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