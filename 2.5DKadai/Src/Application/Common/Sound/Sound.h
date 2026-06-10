#pragma once

enum class SEType
{
	NoneSE = -1,
	ShotSE,
	BOSSShotSE,
	LaserSE,
	BarrierSE,
	DecisionSE,
	NormalExplosionSE,
	BOSSExplosionSE,
	SENUM
};
enum class BGMType
{
	NoneBGM = -1,
	TitleBGM,
	GameBGM,
	ResultBGM,
	BGMNUM
};

//いらないかも
class Sound
{
public:

	void Init(){}
	void Update(){}

	void SetPlaySE(SEType type){}
	void SetPlayBGM(BGMType type){}

	void StopSE(SEType type = SEType::NoneSE){}
	void StopBGM(BGMType type = BGMType::NoneBGM){}

	void Release(){}
private:
	

	std::vector<std::shared_ptr<KdSoundEffect>> m_ses = {};
	std::vector<std::shared_ptr<KdSoundInstance>> m_playSEList = {};

	std::vector<std::shared_ptr<KdSoundEffect>> m_bgms = {};
	std::vector<std::shared_ptr<KdSoundInstance>> m_bgmInss = {};

	float m_sevol = 0;
	float m_bgmvol = 0;

private:
	Sound(){}
	~Sound(){}

public:
	static Sound& GetInstance()
	{
		static Sound instans;
		return instans;
	}
};

#define SOUND Sound::GetInstance()