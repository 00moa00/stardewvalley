#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
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

	virtual bool MouseClick() {

		std::vector<GameEngineCollision*> ColList;
		return (ItemCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));

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
	bool InMouse = false;
private:


};

