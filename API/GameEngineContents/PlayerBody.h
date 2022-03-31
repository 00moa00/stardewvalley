#pragma once
#include <GameEngine/GameEngineActor.h>
#include "PlayerState.h"

enum class PLAYER_STATE {
	INIT = 0,
	MOVE,
};


// Ό³Έν :
class PlayerBody : public GameEngineActor, public PlayerState
{
public:
	// constrcuter destructer
	PlayerBody();
	~PlayerBody();

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
	PlayerBody(const PlayerBody& _Other) = delete;
	PlayerBody(PlayerBody&& _Other) noexcept = delete;
	PlayerBody& operator=(const PlayerBody& _Other) = delete;
	PlayerBody& operator=(PlayerBody&& _Other) noexcept = delete;

protected:

private:

	float Speed_;
	float Energy_;
	float WalkAnimationFrame_;

	GameEngineRenderer* PlayerBody_;
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

