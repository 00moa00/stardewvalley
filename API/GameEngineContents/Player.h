#pragma once

#include "RendererEnum.h"
#include <GameEngine/GameEngineActor.h>
#include "PlayerData.h"
#include "Hoe.h"
#include "Mouse.h"
#include "Inventory.h"
#include "GameData.h"
#include "FixedPlayerColl.h"
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
	const char* ArrAnimationName[static_cast<int>(PLAYERSTATE::MAX)];

	float4 CameraPos_;

	//void moveX();
	//void moveY();



public:

	void SetSpeed(float f) {
		Speed_ = f;
	}

	void SetBreakMove(bool b) {
		BreakMove_ = b;
	}


	bool GetBreakY() {
		return BreakMove_;
	}

	float4 CurrentDir() {
		return MoveDir_;
	}
	GameEngineRenderer* Renderer() {
		return PlayerRenderer_;
	}


private:

	float AnimationFrame_;
	float Speed_;
	float Energy_;
	float4 MoveDir_;
	float4 MovePrevDir_;


	bool BreakMove_;

	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* PlayerRenderer_;
	GameEngineCollision* PlayerCollider_;
	Mouse* Mouse_;
	FixedPlayerColl* FixedPlayerColl_;
	Inventory* Inventory_;
	PLAYERSTATE PlayerState_;
	GameEngineImage* MapColImage_;
	Hoe* Hoe_;

	static std::string CurrentLevel_;
	static std::string PrevLevel_;

private:

	bool isStop();
	bool isMove();

	void SetDirAnimation();
	void SetCamera();

	void PlayerWalk();
	void PlayerDirCheck();
	void PlayerCollCheck();
	void SetColl();
	void SetPlayerStartPos();

	std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameConstRef();
	}


	bool PlayerMouseClickCollision() {

		return (PlayerCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
			&& (Mouse_->isMouseClick());
	}

	bool MoveFarmCollision() {

		return (PlayerCollider_->CollisionResult("MoveFarm", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	bool MoveHouseCollision() {

		return (PlayerCollider_->CollisionResult("MoveHouse", ColList, CollisionType::Rect, CollisionType::Rect));
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

	void DirAnimationChange();
	

	std::string GetDirString();

	void SubEnergy() {
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	
};

