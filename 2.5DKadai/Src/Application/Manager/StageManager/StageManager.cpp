#include "StageManager.h"
#include"../../Scene/SceneManager.h"
#include"../../Common/Info/Info.h"

#include"../../Object/StageBlock/BaseStageBlock.h"
#include"../../Object/Player/Player.h"
#include"../../Object/StageBlock/DamageBlock/DamageBlock.h"
#include"../../Object/Item/Coin/Coin.h"
#include"../../Object/Event/RoomExit/RoomExit.h"
#include"../../Object/Event/Goal/Goal.h"
#include"../../Object/Event/RoomCenter/RoomCenter.h"

void StageManager::Init()
{
	//////////生成するオブジェクト追加////////////
	//プレイヤー
	m_createObjInfo.push_back({ "Player", []()
		{
			std::shared_ptr<Player> player = std::make_shared<Player>();
			player->Init();
			return player;
		} });
	//ブロック
	m_createObjInfo.push_back({ "Block",[]()
		{
			std::shared_ptr<BaseStageBlock> block = std::make_shared<BaseStageBlock>();
			block->SetAsset("Block");
			block->Init();
			return block;
		} });
	//棘
	m_createObjInfo.push_back({ "Dorn",[]()
		{
			std::shared_ptr<DamageBlock> dorn = std::make_shared<DamageBlock>();
			dorn->SetAsset("Dorn");
			dorn->Init();
			return dorn;
		} });
	//コイン
	m_createObjInfo.push_back({ "Coin",[]()
		{
			std::shared_ptr<Coin> coin = std::make_shared<Coin>();
			coin->Init();
			return coin;
		} });
	//部屋の出口判定
	m_createObjInfo.push_back({ "RoomExit",[]()
		{
			std::shared_ptr<RoomExit> roomexit = std::make_shared<RoomExit>();
			roomexit->Init();
			return roomexit;
		} });
	//ゴール判定
	m_createObjInfo.push_back({ "Goal",[]()
		{
			std::shared_ptr<Goal> goal = std::make_shared<Goal>();
			goal->Init();
			return goal;
		} });
	//部屋の中心
	m_createObjInfo.push_back({ "RoomCenter",[]()
		{
			std::shared_ptr<RoomCenter> roomcenter = std::make_shared<RoomCenter>();
			return roomcenter;
		} });

	///////////////////////////////////////////////
}

void StageManager::StageLoad(const std::string& _filename)
{
	//始めに前のステージ情報初期化
	m_currentRoomId = 0;
	m_oldroomcenter = nullptr;
	m_currentroomcenter = nullptr;
	m_filename.clear();

	FILE* fp = nullptr;

	std::string path =
		"Asset/Data/StageData/Stage" +
		_filename +
		".csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp) return;

	char dummy[255];

	fgets(dummy, 255, fp);		//1行飛ばす


	Math::Vector3  pos = {};
	std::vector<Math::Vector3>  poskeeplist = {};

	char filename[256] = "";

	char line[256];

	//一行読み込み
	while (fgets(line, sizeof(line), fp))
	{
		//ルーム情報
		//１項目読み込めたら
		if (sscanf_s(line,"%255[^,\n]",filename,(unsigned)_countof(filename)) == 1)
		{
			m_filename.push_back(filename);
		}
	}

	fclose(fp);

	//3つ目までのルーム（最初のルーム）をロード
	FirstRoomLoad();
}

void StageManager::FirstRoomLoad()
{
	if (m_filename.size() < InitialRoomCount)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::StageSelect);
		return;
	}
	
	//初期生成数まで
	//2つ目までのルーム（最初のルーム）をロード
	for (int i = 0; i < InitialRoomCount; i++)
	{
		//ルーム生成
		LoadRoom(m_filename[i],m_currentRoomId);

		m_currentRoomId++;
	}

	//初期生成時に変更してしまっているがプレイヤーは0から始まらないといけないので0に戻す
	m_currentRoomId = 0;
}

void StageManager::ChangeRoom()
{
	//3個先の部屋のID
	int nextid = m_currentRoomId + 3;
	//2個前の部屋のID
	int	previousid = m_currentRoomId - 2;

	//2個前の部屋削除
	UnLoadRoom(previousid);

	//次の部屋が存在するときだけ生成

	if (nextid < m_filename.size())
	{
		//3個先の部屋生成
		LoadRoom(m_filename[nextid], nextid);
	}
	else
	{
		// 最後の部屋をもう一度生成
		LoadRoom(m_filename.back(), nextid);
	}
	
	//更新
	m_currentRoomId++;
}

void StageManager::LoadRoom(const std::string& _filename, int _instanceId)
{
	if (_instanceId < 0)return;

	m_currentroomcenter = nullptr;

	FILE* fp = nullptr;

	std::string path =
		"Asset/Data/StageData/RoomData/Room" +
		_filename +
		".csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp) return;

	char objName[256] = "";

	Math::Vector3 pos = {};
	Math::Vector3 rot = {};
	Math::Vector3 scale = {};

	//部屋の間隔
	Math::Vector3 spacing =  Math::Vector3::Zero;
	Math::Vector3 oldroomcenterpos = Math::Vector3::Zero;
	//始めの部屋のみ座標調整不要
	if (m_oldroomcenter)
	{
		spacing = INFO.GetRoomSpacing();
		//一個前の部屋の中心座標取得
		oldroomcenterpos = m_oldroomcenter->GetPos();
	}

	//座標調整最終
	Math::Vector3 roomorigin = oldroomcenterpos + spacing;

	while (fscanf_s(fp,"%255[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f\n"
		,objName,(unsigned)_countof(objName),&pos.x,&pos.y,&pos.z,
		&rot.x,&rot.y,&rot.z,
		&scale.x,&scale.y,&scale.z) == 10)
	{
		for (auto& createInfo : m_createObjInfo)
		{
			if (createInfo.name != objName)continue;

			auto obj = createInfo.obj();

			obj->SetName(createInfo.name);			

			obj->SetPos(pos + roomorigin);

			obj->SetSize(scale);
			obj->SetRot(rot);

			obj->SetInstanceID(_instanceId);

			SceneManager::Instance().AddObject(obj);

			//生成したのが部屋の中心なら
			if (createInfo.name == "RoomCenter")
			{
				m_currentroomcenter = obj;
			}

			break;
		}
	}

	fclose(fp);

	int id = KdRandom::GetInt(0, 5);

	char buf[256];

	sprintf_s(buf,
		"Asset/Data/StageData/BackGroundObjectData/%02d_BackGroundObject.csv",
		id);
	path = buf;

	fopen_s(&fp, path.c_str(), "r");

	if (fp)
	{
		char line[256];

		//一行読み込み
		while (fgets(line, sizeof(line), fp))
		{
			//４項目読み込めたら
			if (sscanf_s(line, "%255[^,],%f,%f,%f\n", objName, (unsigned)_countof(objName), &pos.x, &pos.y, &pos.z) == 4)
			{
				for (auto& createInfo : m_createObjInfo)
				{
					if (createInfo.name != objName)continue;

					auto obj = createInfo.obj();

					obj->SetName(createInfo.name);

					obj->SetPos(pos + roomorigin);

					obj->SetInstanceID(_instanceId);

					SceneManager::Instance().AddObject(obj);

					break;

				}
			}
		}
		fclose(fp);
	}
	//部屋の中心座標更新
	if (!m_currentroomcenter)return;
	m_oldroomcenter = m_currentroomcenter;
}

void StageManager::LoadRoom(const std::string& _filename)
{
	FILE* fp = nullptr;

	std::string path =
		"Asset/Data/StageData/RoomData/Room" +
		 _filename +
		".csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp) return;

	char objName[256] = "";

	Math::Vector3 pos = {};
	Math::Vector3 rot = {};
	Math::Vector3 scale = {};

	while (fscanf_s(fp, "%255[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f\n"
		, objName, (unsigned)_countof(objName), &pos.x, &pos.y, &pos.z,
		&rot.x, &rot.y, &rot.z,
		&scale.x, &scale.y, &scale.z) == 10)
	{
		for (auto& createInfo : m_createObjInfo)
		{
			if (createInfo.name != objName)continue;
			
			auto obj = createInfo.obj();

			obj->SetName(createInfo.name);

			obj->SetPos(pos);
			obj->SetSize(scale);
			obj->SetRot(rot);

			obj->SetInstanceID(-1);

			SceneManager::Instance().AddObject(obj);

			break;
			
		}
	}

	int id = KdRandom::GetInt(0, 5);

	char buf[256];

	sprintf_s(buf,
		"Asset/Data/StageData/BackGroundObjectData/%02d_BackGroundObject.csv",
		id);
	path = buf;

	fopen_s(&fp, path.c_str(), "r");

	if (!fp)return;

	char line[256];

	//一行読み込み
	while (fgets(line, sizeof(line), fp))
	{
		//４項目読み込めたら
		if (sscanf_s(line, "%255[^,],%f,%f,%f\n", objName, (unsigned)_countof(objName), &pos.x, &pos.y, &pos.z) == 4)
		{
			for (auto& createInfo : m_createObjInfo)
			{
				if (createInfo.name != objName)continue;

				auto obj = createInfo.obj();

				obj->SetName(createInfo.name);

				obj->SetPos(pos);

				obj->SetInstanceID(-1);

				SceneManager::Instance().AddObject(obj);

				break;

			}
		}
	}

	fclose(fp);
}

void StageManager::UnLoadRoom(int instanceId)
{
	if (instanceId < 0)return;

	auto& objList =
		SceneManager::Instance().GetObjList();

	for (auto& obj : objList)
	{
		if (!obj) continue;

		if (obj->GetInstanceID() == instanceId)
		{
			obj->SetExpired();
		}
	}
}
