#pragma once
#include "PlayerShirts.h"

#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Player : public GameEngineActor, public PlayerState
{
public:
	// constrcuter destructer
	Player();
	~Player();


	PlayerShirts* PlayerShirts_;

	void init();
	void update();
	void release();


	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	static Player* Inst_;

};

