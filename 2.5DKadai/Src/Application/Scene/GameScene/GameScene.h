#pragma once

#include"../BaseScene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr<Player> m_player;

	//部屋番号管理用
	int m_currentRoomId = 0;
	void ChangeRoom(std::string nextFile, int nextId);

};
