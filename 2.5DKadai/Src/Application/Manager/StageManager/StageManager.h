#pragma once

class StageManager
{
public:
	
	void StageLoad(const std::string& _filename);
	void ChangeRoom();

	void LoadRoom(const std::string& _filename);

	//特定のルームを一つだけ出したいとき用（タイトルなど）
	//void LoadOneRoom(const std::string& _filename, const Math::Vector3& _pos = { 0,0,0 });

private:

	void Init();

	//3つ目までのルーム（最初のルーム）をロード
	void FirstRoomLoad();

	void LoadRoom(const std::string& _filename ,int _instanceId);
	void UnLoadRoom(int _instanceId);

	//ステージごとのなんのルームを呼び出すかを格納
	std::vector<std::string> m_filename;

	struct CreateObjInfo
	{
		std::string name;
		std::function<std::shared_ptr<KdGameObject>()> obj;
	};

	std::vector<CreateObjInfo> m_createObjInfo;

	//部屋番号管理用
	int m_currentRoomId = 0;

	//一つ前の部屋の中心を保存
	std::shared_ptr<KdGameObject> m_oldroomcenter;
	std::shared_ptr<KdGameObject> m_currentroomcenter;

	//初期生成部屋数
	static const int InitialRoomCount = 2;

private:
	StageManager() { Init(); }
	~StageManager() {}
public:

	static StageManager& Instance()
	{
		static StageManager instance;
		return instance;
	}
};

#define STAGEMANAGER StageManager::Instance()