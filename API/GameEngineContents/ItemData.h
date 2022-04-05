#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include "ItemCode.h"

class ItemData {

public:

	ItemData()
		:
		ItemRenderer_(nullptr),
		ItemCollider_(nullptr)
	{

	}
	~ItemData() {};


	GameEngineRenderer* ItemRenderer_ = nullptr;
	GameEngineCollision* ItemCollider_ = nullptr;
	bool InMouse = false;

	GameEngineCollision* getCollision() {
		return ItemCollider_;
	}
	GameEngineRenderer* getRenderer() {
		return ItemRenderer_;
	}

	bool MouseClick() {

		std::vector<GameEngineCollision*> ColList;
		return (ItemCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));

	}


};