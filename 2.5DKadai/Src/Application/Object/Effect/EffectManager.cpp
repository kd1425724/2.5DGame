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

		//','ごとに取り出す
		std::getline(ss, name, ',');
		std::getline(ss, asset, ',');
		std::getline(ss, splitX, ',');
		std::getline(ss, splitY, ',');
		std::getline(ss, anim, ',');
		std::getline(ss, speed, ',');
		std::getline(ss, scale, ',');

		EffectData data;

		data.assetName = "Asset/Textures/Effect/" + asset;

		//数値に変換（int）
		data.splitX = std::stoi(splitX);
		data.splitY = std::stoi(splitY);
		//(float)
		data.animSpeed = std::stof(speed);
		//サイズ
		data.scale = std::stof(scale);

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
	const Math::Vector3& pos,
	UINT flag)
{
	auto effect = CreateBaseEffect(
		name,
		pos,
		flag);

	if (!effect) return;

	SceneManager::Instance().AddObject(effect);
}

void EffectManager::CreateEffectHoming(
	const std::string& name,
	const Math::Vector3& pos,
	const Math::Vector3& targetPos,
	UINT flag,
	float homingspeed)
{
	auto effect = CreateBaseEffect(
		name,
		pos,
		flag|eHoming);

	if (!effect) return;

	effect->SetTargetPos(targetPos);
	effect->SetHomingSpeed(homingspeed);

	SceneManager::Instance().AddObject(effect);
}

void EffectManager::CreateEffectHoming(
	const std::string& name,
	const Math::Vector3& pos,
	const std::shared_ptr<KdGameObject>& targetObj,
	UINT flag,
	float homingspeed)
{
	auto effect = CreateBaseEffect(
		name,
		pos,
		flag | eHoming);

	if (!effect) return;

	effect->SetTarget(targetObj);
	effect->SetHomingSpeed(homingspeed);

	SceneManager::Instance().AddObject(effect);
}

std::shared_ptr<BaseEffect> EffectManager::CreateBaseEffect(
	const std::string& name,
	const Math::Vector3& pos,
	UINT flag)
{
	auto it = m_effectTable.find(name);

	if (it == m_effectTable.end()) return nullptr;

	auto effect = std::make_shared<BaseEffect>();

	effect->SetAsset(it->second.assetName);

	effect->SetSplit(
		it->second.splitX,
		it->second.splitY);

	effect->SetAnim(
		it->second.anim);

	effect->SetAnimSpeed(
		it->second.animSpeed);

	effect->SetPos(pos);

	effect->SetSize(it->second.scale);

	effect->SetFlag(flag);

	effect->Init();

	return effect;
}