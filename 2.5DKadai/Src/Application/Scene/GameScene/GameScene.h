#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class GameSceneUi;
class CountDown;

class GameScene : public BaseScene
{
public :

	GameScene()  {}
	~GameScene() {}

	void Init()  override;

private:

	enum class GamePattern
	{
		Stop,
		CountDown,
		Start,
		Game
	};

	GamePattern m_gamepattern = GamePattern::Stop;

	void Event() override;
	

	std::weak_ptr<Player> m_player;

	std::shared_ptr<GameSceneUi> m_gamesceneui;

	std::shared_ptr<CountDown> m_countdown;

};
