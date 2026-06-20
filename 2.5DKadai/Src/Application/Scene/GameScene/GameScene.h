#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class GameSceneUi;
class CountDown;

class GameScene : public BaseScene
{
public :

	GameScene(const std::string& stagepath)
	{
		m_stagepath = stagepath;
	}
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

	std::string m_stagepath = "";

	GamePattern m_gamepattern = GamePattern::Stop;

	void Event() override;
	

	std::weak_ptr<Player> m_player;

	std::shared_ptr<GameSceneUi> m_gamesceneui;

	std::shared_ptr<CountDown> m_countdown;

	int m_goalcnt = 0;

};
