#include "EffectManager.h"
#include"../../Scene/SceneManager.h"
#include"BaseEffect.h"

void EffectManager::Init()
{
	FILE* fp=nullptr;
	
	std::string path = "Asset/Data/ObjectData/EffectData/EffectData.csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp)return;

	char line[1024];

	// ヘッダを飛ばす
	fgets(line, sizeof(line), fp);

	while (fgets(line, sizeof(line), fp))
	{
		// 1行を文字列ストリームに変換
		std::stringstream ss(line);

		std::string name;
		std::string asset;
		std::string splitX;
		std::string splitY;
		std::string anim;
		std::string speed;
		std::string scale;
		std::string loop;

		//','ごとに取り出す
		std::getline(ss, name, ',');
		std::getline(ss, asset, ',');
		std::getline(ss, splitX, ',');
		std::getline(ss, splitY, ',');
		std::getline(ss, anim, ',');
		std::getline(ss, speed, ',');
		std::getline(ss, scale, ',');
		std::getline(ss, loop);

		EffectData data;

		data.assetName = "Asset/Textures/Effect/" + asset;

		//数値に変換（int）
		data.splitX = std::stoi(splitX);
		data.splitY = std::stoi(splitY);
		//(float)
		data.animSpeed = std::stof(speed);
		//サイズ
		data.scale = std::stof(scale);
		//(int)
		data.loop = std::stoi(loop);

		// アニメーション配列
		//stringstream...文字列をファイルのように扱う
		std::stringstream animSS(anim);

		std::string frame;

		//'|'がでて来るまで読む
		while (std::getline(animSS, frame, '|'))
		{
			//数値に変換して代入
			data.anim.push_back(std::stoi(frame));
		}

		//名前をキーにして登録
		m_effectTable[name] = data;
	}

	fclose(fp);
}

void EffectManager::CreateEffect(
	const std::string& name,
	const Math::Vector3& pos)
{
	auto it = m_effectTable.find(name);

	if (it == m_effectTable.end()) return;

	auto effect = std::make_shared<BaseEffect>();

	effect->SetAsset(it->second.assetName);

	effect->SetSplit(
		it->second.splitX,
		it->second.splitY);

	effect->SetAnim(
		it->second.anim);

	effect->SetAnimSpeed(
		it->second.animSpeed);

	effect->SetLoop(
		it->second.loop);

	effect->SetPos(pos);

	effect->SetSize(it->second.scale);

	effect->Init();

	SceneManager::Instance().AddObject(effect);
}