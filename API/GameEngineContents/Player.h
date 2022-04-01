#pragma once
#include "PlayerShirts.h"
#include "PlayerBody.h"
#include "PlayerHair.h"
#include "PlayerPants.h"
#include "PlayerShirts.h"
#include "PlayerHand.h"
#include <GameEngine/GameEngineActor.h>

enum class PLAYER_STATE {
	INIT = 0,
	MOVEEFFECT,
	MOVE,
};

class PlayerMove;

class Player : public GameEngineActor
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

	void SubEnergy() {
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}

	void moveX();
	void moveY();

	bool isStop();
	bool isMove();

	void PlayerActorSetPos();

	void SetInit();
	void SetDir();
	void SetAllPivot(float _MovePosY);

	void SetMoveEffect();


	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;


private:

	float WalkAnimationFrame_;

	float Speed_;
	int MoveEffectTimer_;

	int MoveEffectState_;
	float PivotY_;
	float PivotYSpeed_;

	float Energy_;

	unsigned int ShirtIndex_;
	unsigned int PantsIndex_;
	unsigned int HairIndex_;

	PLAYER_STATE PlayerState_;

	PlayerShirts* PlayerShirts_;
	PlayerBody* PlayerBody_;
	PlayerHand* PlayerHand_;
	PlayerHair* PlayerHair_;
	PlayerPants* PlayerPants_;



private:

	struct PlayerMove {

	public:
		bool isFrontWalk_ = false;
		bool isBackWalk_ = false;
		bool isRightWalk_ = false;
		bool isLeftWalk_ = false;
		bool isInit_ = false;

		void SetFrontWalk(bool b) {
			isFrontWalk_ = b;
			isBackWalk_ = false;
			isRightWalk_ = false;
			isLeftWalk_ = false;
		}

		void SetBackWalk(bool b) {
			isFrontWalk_ = false;
			isBackWalk_ = b;
			isRightWalk_ = false;
			isLeftWalk_ = false;
		}

		void setRightWalk(bool b) {
			isFrontWalk_ = false;
			isBackWalk_ = false;
			isRightWalk_ = b;
			isLeftWalk_ = false;
		}

		void SetLeftWalk(bool b) {
			isFrontWalk_ = false;
			isBackWalk_ = false;
			isRightWalk_ = false;
			isLeftWalk_ = b;
		}

		void SetWalkInit(bool b) {

			isInit_ = b;
		}
	} PlayerMove_;
};

