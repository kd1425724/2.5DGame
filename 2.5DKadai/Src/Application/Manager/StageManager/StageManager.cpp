#include "StageManager.h"
#include"../../Scene/SceneManager.h"

#include"../../Object/StageBlock/BaseStageBlock.h"
#include"../../Object/Player/Player.h"
#include"../../Object/StageBlock/DamageBlock/DamageBlock.h"
#include"../../Object/Item/Coin/Coin.h"
#include"../../Object/Event/RoomExit/RoomExit.h"
#include"../../Object/Event/Goal/Goal.h"

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

	///////////////////////////////////////////////
}

void StageManager::StageLoad(const std::string& _filename)
{
	m_currentRoomId = 0;

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
	
	while (fscanf_s(fp,"%*[^,],%*[^,],%f,%f,%f", &pos.x, &pos.y, &pos.z) == 3)
	{
		poskeeplist.push_back(pos);
	}

	fgets(dummy, 255, fp);		//1行飛ばす
	fgets(dummy, 255, fp);		//1行飛ばす

	char filename[256] = "";

	StageFileData data;

	int id = 1;

	char line[256];

	//一行読み込み
	while (fgets(line, sizeof(line), fp))
	{
		//座標情報
		//３項目読み込めたら
		if (sscanf_s(line, "%*[^,],%*[^,],%f,%f,%f", &pos.x, &pos.y, &pos.z) == 3)
		{
			poskeeplist.push_back(pos);
		}
		//ルーム情報
		//２項目読み込めたら
		else if (sscanf_s(line,"%255[^,],%d",filename,(unsigned)_countof(filename),&id) == 2)
		{
			data.filename = filename;
			data.pos = poskeeplist[id];

			m_filedata.push_back(data);
		}
	}

	fclose(fp);

	//3つ目までのルーム（最初のルーム）をロード
	FirstRoomLoad();
}

void StageManager::FirstRoomLoad()
{
	if (m_filedata.size() < 3)return;

	//3つ目までのルーム（最初のルーム）をロード
	for (int i = 0; i < 3; i++)
	{
		//ルーム生成
		LoadRoom(m_filedata[m_currentRoomId],m_currentRoomId);

		//現在のルームID更新
		m_currentRoomId++;
	}
}

void StageManager::ChangeRoom()
{
	//2個先の部屋のID
	int nextid = m_currentRoomId + 2;
	//1個前の部屋のID
	int	previousid = m_currentRoomId - 1;

	//1個前の部屋削除
	UnLoadRoom(previousid);

	//2個先の部屋生成
	LoadRoom(m_filedata[nextid],nextid);

	//更新
	m_currentRoomId++;
}

void StageManager::LoadRoom(const StageFileData& _filedata, int _instanceId)
{
	if (_instanceId < 0)return;

	FILE* fp = nullptr;

	std::string path =
		"Asset/Data/StageData/RoomData/Room" +
		_filedata.filename +
		".csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp) return;

	char objName[256] = "";

	Math::Vector3 pos;

	while (fscanf_s(fp,"%255[^,],%f,%f,%f\n",objName,(unsigned)_countof(objName),&pos.x,&pos.y,&pos.z) == 4)
	{
		for (auto& createInfo : m_createObjInfo)
		{
			if (createInfo.name != objName)continue;

			auto obj = createInfo.obj();

			obj->SetName(createInfo.name);

			obj->SetPos(pos + _filedata.pos);

			obj->SetInstanceID(_instanceId);

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

				obj->SetPos(pos + _filedata.pos);

				obj->SetInstanceID(_instanceId);

				SceneManager::Instance().AddObject(obj);

				break;

			}
		}
	}

	fclose(fp);
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

	Math::Vector3 pos;

	while (fscanf_s(fp, "%255[^,],%f,%f,%f\n", objName, (unsigned)_countof(objName), &pos.x, &pos.y, &pos.z) == 4)
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
