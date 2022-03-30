#pragma once
#include <GameEngine/GameEngineActor.h>
#include "PlayerState.h"

enum class PLAYER_STATE {
	INIT = 0,
	MOVE,
};


// Ό³Έν :
class Player : public GameEngineActor, public PlayerState
{
public:
	// constrcuter destructer
	Player();
	~Player();

	float GetEnergy() {
		return Energy_;
	}

	void SetPlayerSpeed(float f) {
		Speed_ = f;
	}

	float GetPlayerSpeed() {
		return Speed_;
	}


	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:

	float Speed_;
	float Energy_;

//	bool isInit_;

	GameEngineRenderer* PlayerBody_;
	GameEngineRenderer* PlayerHand_;
	PLAYER_STATE PlayerState_;

	void moveX();
	void moveY();
	void SubEnergy() {
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	bool isStop();
	bool isMove();
	void SetInit();

	void Start() override;
	void Update() override;
	void Render() override;
};

