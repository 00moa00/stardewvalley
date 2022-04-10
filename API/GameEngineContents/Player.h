#pragma once

#include "RendererEnum.h"
#include <GameEngine/GameEngineActor.h>
#include "PlayerData.h"
#include "Hoe.h"
#include "Mouse.h"
#include "Inventory.h"
#include "GameData.h"
#include <list>

//class PlayerMove;

class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

protected:
	void Start() override;
	void Update() override;
	void Render() override;

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private:

	float4 CameraPos_;

	void moveX();
	void moveY();

	bool isStop();
	bool isMove();
	void SetDirAnimation();
	void SetCamera();

	//void SetInit();

public:
	void SetSpeed(float f) {
		Speed_ = f;
	}

	float4 CurrentDir() {
		return MoveDir_;
	}


private:

	float AnimationFrame_;
	float Speed_;
	float Energy_;
	float4 MoveDir_;

	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* PlayerRenderer_;
	GameEngineCollision* PlayerCollider_;
	Mouse* Mouse_;

	Inventory* Inventory_;
	PLAYERSTATE PlayerState_;


	//��
	Hoe* Hoe_;

private:

	bool PlayerMouseCollision() {
		std::vector<GameEngineCollision*> ColList;

		return (PlayerCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
			&& (Mouse_->isMouseClick());
	}


	float GetEnergy() {
		return Energy_;
	}

	void SetPlayerSpeed(float f) {
		Speed_ = f;
	}

	float GetPlayerSpeed() {
		return Speed_;
	}

	

	void SubEnergy() {
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	
};

