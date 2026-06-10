#include "EnemyBase.h"

void EnemyBase::DataLoad(std::string _filename)
{
	FILE* fp;

	//ファイルの名前
	std::string path = "Asset/Data/ObjectData/EnemyData/" + _filename + "Data/" + _filename + "Data.csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp)return;

	char dummy[255];

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/GameScene/Enemy/" + _filename + "/" + _filename + ".csv");

	fgets(dummy, 255, fp);		//1行飛ばす

	//サイズ倍率
	float scalenum = 0;
	fscanf_s(fp, "%*[^,],%f\n", &scalenum);
	m_polygon->SetScale(scalenum);

	fgets(dummy, 255, fp);		//1行飛ばす

	//画像分割
	fgets(dummy, 255, fp);		//1行飛ばす
	Math::Vector2 uvrect = {};
	fscanf_s(fp, "%*[^,],%f,%f\n", &uvrect.x, &uvrect.y);
	m_polygon->SetSplit(uvrect.x, uvrect.y);
	//アニメーション
	fgets(dummy, 255, fp);		//1行飛ばす
	fgets(dummy, 255, fp);		//1行飛ばす
	int animnum = 0;
	fscanf_s(fp, "%*[^,],%d\n", &animnum);
	//配列数をアニメーション数に合わせる
	m_animidkeep.resize(animnum);

	fgets(dummy, 255, fp);		//1行飛ばす
	//アニメーションID読み込み
	for (int i = 0; i < animnum; i++)
	{
		//始めだけ飛ばす
		fscanf_s(fp, "%*[^,]");

		for (int j = 0; j < 20; j++)
		{
			int animid = 0;
			//一個ずつ読み込む
			fscanf_s(fp, ",%d\n", &animid);
			//もし-1（最後まで読んだ）ならbreak
			if (animid == -1)
			{
				fgets(dummy, 255, fp);		//1行飛ばす
				break;
			}

			m_animidkeep[i].push_back(animid);
		}
	}
	fclose(fp);

}

void EnemyBase::UVRectControlUpdate()
{
	if (!m_animflg)return;
	if (m_loopmax <= 0)return;

	m_anim += m_animmax / (float)m_animtime;

	if (m_anim >= m_animmax)
	{
		m_animcnt--;

		//animcntが０になるまでループ
		if (m_animcnt <= 0)
		{
			//アニメーション初期化
			m_anim = 0;
			//アニメーションフラグ初期化
			m_animflg = false;
			//上書き可能に戻す
			m_overwritable = true;

			if (m_action)
			{
				m_action();
			}

			//共通で行うアクション
			if (m_commonanimfinishdaction)
			{
				m_commonanimfinishdaction();
			}
			return;
		}

		m_anim = 0;

	}

	//アニメーション
	m_polygon->SetUVRect(m_animid[(int)m_anim]);
}

void EnemyBase::UVRectControlInit()
{
	m_anim = 0;

	//始めに初期化
	m_animid.clear();
	m_action = nullptr;
}
