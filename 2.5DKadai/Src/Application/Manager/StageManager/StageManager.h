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

	struct StageFileData
	{
		std::string filename = "";
		Math::Vector3 pos = {};
	};

	//3つ目までのルーム（最初のルーム）をロード
	void FirstRoomLoad();

	void LoadRoom(const StageFileData& _filedata ,int _instanceId);
	void UnLoadRoom(int _instanceId);

	//ステージごとのなんのルームを呼び出すかを格納
	std::vector<StageFileData> m_filedata;

	struct CreateObjInfo
	{
		std::string name;
		std::function<std::shared_ptr<KdGameObject>()> obj;
	};

	std::vector<CreateObjInfo> m_createObjInfo;

	//部屋番号管理用
	int m_currentRoomId = 0;

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