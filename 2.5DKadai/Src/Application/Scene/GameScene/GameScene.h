#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class GameSceneUi;

class GameScene : public BaseScene
{
public :

	GameScene()  {}
	~GameScene() {}

	void Init()  override;

private:

	void Event() override;
	

	std::weak_ptr<Player> m_player;

	std::shared_ptr<GameSceneUi> m_gamesceneui;

};
