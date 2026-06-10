//#include "Sound.h"
//
//void Sound::Init()
//{
//	m_sevol = 1.0f;
//	m_bgmvol = 1.0f;
//
//	m_ses.resize((int)SEType::SENUM);
//
//	for (int i = 0; i < (int)SEType::SENUM; i++)
//	{
//		m_ses[i] = std::make_shared<KdSoundEffect>();
//	}
//
//	m_ses[(int)SEType::ShotSE]->Load("SoundMaterials/SE/Skill/ShotSE.wav");
//
//	m_ses[(int)SEType::BOSSShotSE]->Load("SoundMaterials/SE/Skill/BOSSShotSE.wav");	
//
//	m_ses[(int)SEType::LaserSE]->Load("SoundMaterials/SE/Skill/LaserSE.wav");
//
//	m_ses[(int)SEType::BarrierSE]->Load("SoundMaterials/SE/Skill/BarrierSE.wav");
//
//	m_ses[(int)SEType::DecisionSE]->Load("SoundMaterials/SE/System/DecisionSE.wav");
//
//	m_ses[(int)SEType::NormalExplosionSE]->Load("SoundMaterials/SE/Explosion/NormalExplosionSE.wav");
//
//	m_ses[(int)SEType::BOSSExplosionSE]->Load("SoundMaterials/SE/Explosion/BOSSExplosionSE.wav");
//
//
//	m_bgms.resize((int)BGMType::BGMNUM);
//	m_bgmInss.resize((int)BGMType::BGMNUM);
//
//	for (int i = 0; i < (int)BGMType::BGMNUM; i++)
//	{
//		m_bgms[i] = std::make_shared<KdSoundEffect>();
//	}
//
//	m_bgms[(int)BGMType::TitleBGM]->Load("SoundMaterials/BGM/TitleBGM.wav");
//	m_bgmInss[(int)BGMType::TitleBGM] =
//		m_bgms[(int)BGMType::TitleBGM]->CreateInstance(false);
//
//	m_bgms[(int)BGMType::GameBGM]->Load("SoundMaterials/BGM/GameBGM.wav");
//	m_bgmInss[(int)BGMType::GameBGM] =
//		m_bgms[(int)BGMType::GameBGM]->CreateInstance(false);
//
//	m_bgms[(int)BGMType::ResultBGM]->Load("SoundMaterials/BGM/ResultBGM.wav");
//	m_bgmInss[(int)BGMType::ResultBGM] =
//		m_bgms[(int)BGMType::ResultBGM]->CreateInstance(false);
//}
//void Sound::Update()
//{
//	for (int i = (int)m_playSEList.size() - 1; i >= 0; i--)
//	{
//		//終わったら消去
//		if (!m_playSEList[i]->IsPlaying())
//		{
//			m_playSEList.erase(m_playSEList.begin() + i);
//		}
//	}
//}
//void Sound::SetPlaySE(SEType type)
//{
//	int idx = (int)type;
//
//	if (idx < 0 || idx >= (int)m_ses.size()) return;
//
//	auto se = m_ses[idx];
//
//	if (!se) return;
//
//	auto inst = se->CreateInstance();
//
//	if (!inst) return;
//
//	float multiplicationvol = 1.0f;
//
//	switch (type)
//	{
//	case SEType::NoneSE:
//		break;
//	case SEType::ShotSE:
//		multiplicationvol = 0.15f;
//		break;
//	case SEType::BOSSShotSE:
//		multiplicationvol = 0.5f;
//		break;
//	case SEType::LaserSE:
//		multiplicationvol = 0.1f;
//		break;
//	case SEType::BarrierSE:
//		multiplicationvol = 0.2f;
//		break;
//	case SEType::DecisionSE:
//		multiplicationvol = 0.7f;
//		break;
//	case SEType::NormalExplosionSE:
//		multiplicationvol = 0.2f;
//		break;
//	case SEType::BOSSExplosionSE:
//		multiplicationvol = 1.0f;
//		break;
//	case SEType::SENUM:
//		break;
//	default:
//		break;
//	}
//
//	float finalvol = m_sevol * multiplicationvol;
//
//	inst->SetVolume(finalvol);
//	inst->Play(false);
//
//	m_playSEList.push_back(inst);
//}
//
//void Sound::SetPlayBGM(BGMType type)
//{
//	int idx = (int)type;
//
//	if (idx < 0 || idx >= (int)m_bgmInss.size()) return;
//
//	StopBGM();
//
//	auto bgm = m_bgmInss[idx];
//
//	if (!bgm) return;
//
//	float multiplicationvol = 1.0f;
//
//	switch (type)
//	{
//	case BGMType::NoneBGM:
//		break;
//	case BGMType::TitleBGM:
//		multiplicationvol = 0.1f;
//		break;
//	case BGMType::GameBGM:
//		multiplicationvol = 0.1f;
//		break;
//	case BGMType::ResultBGM:
//		multiplicationvol = 0.05f;
//		break;
//	case BGMType::BGMNUM:
//		break;
//	default:
//		break;
//	}
//
//	float finalvol = m_bgmvol * multiplicationvol;
//
//	bgm->Stop();
//	bgm->SetVolume(finalvol);
//	bgm->Play(true);
//}
//
//void Sound::StopSE(SEType type)
//{
//	if (type == SEType::NoneSE)
//	{
//		//全部停止
//		for (auto& se : m_playSEList)
//		{
//			if (se)
//			{
//				se->Stop();
//			}
//		}
//
//		m_playSEList.clear();
//	}
//	else
//	{
//		//auto se = m_playSEList;
//
//
//	}
//}
//
//void Sound::StopBGM(BGMType type)
//{
//	if (type == BGMType::NoneBGM)
//	{
//		//全部停止
//		for (auto& bgm : m_bgmInss)
//		{
//			if (bgm)
//			{
//				bgm->Stop();
//			}
//		}
//	}
//	else
//	{
//		auto bgm = m_bgmInss[(int)type];
//
//		if (bgm)
//		{
//			bgm->Stop();
//		}
//	}
//}