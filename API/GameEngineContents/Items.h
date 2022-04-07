#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "ItemCode.h"
#include "ToolEnum.h"

// Ό³Έν :
class Items : public GameEngineActor
{
public:

	GameEngineCollision* getCollision() {

		return ItemCollider_;
	}
	GameEngineRenderer* getRenderer() {

		return ItemRenderer_; 
	}

	bool MouseOver() {
		std::vector<GameEngineCollision*> ColList;

		return (ItemCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool MouseHoldItem() {
		return MouseHoldItem_;
	}

	virtual void UpdateOff() {
		this->Off();
	}

	void SetInMouse(bool b) {
		InMouse = b;
	}

	bool GetInMouse() {
		return InMouse;
	}


	// constrcuter destructer
	Items();
	~Items();

	// delete Function
	Items(const Items& _Other) = delete;
	Items(Items&& _Other) noexcept = delete;
	Items& operator=(const Items& _Other) = delete;
	Items& operator=(Items&& _Other) noexcept = delete;


protected:

	GameEngineRenderer* ItemRenderer_ = nullptr;
	GameEngineCollision* ItemCollider_ = nullptr;
	bool MouseHoldItem_ = false;

private:
	bool InMouse;

};

