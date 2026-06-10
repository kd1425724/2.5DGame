#pragma once

enum class EffectType
{
    Explosion,
};

class EffectManager
{
public:

	void AddEffect(
		EffectType type,
		Math::Vector3 pos = { 0,0,0 },
		Math::Vector3 scale = { 1.0f, 1.0f, 1.0f },
		int time = 0);

private:

private:
    EffectManager() {};
    ~EffectManager() { }

public:
    static EffectManager& GetInstance()
    {
        static EffectManager instance;
        return instance;
    }
};

#define EFFECTMANAGER EffectManager::GetInstance()