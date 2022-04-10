#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "ItemCode.h"
#include "ToolEnum.h"
//#include "Player.h"

// Ό³Έν :

enum class ITEMTYPE{

	ITEM,
	OBJECT,
	TOOL,

};

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

		return (ItemCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool IteminItem() {

		return (ItemCollider_->CollisionResult("Item", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	bool IteminBox() {
	

		return (ItemCollider_->CollisionResult("Box", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool MouseHoldItem() {
		return MouseHoldItem_;
	}
	
	bool IsWall(float4 pos, float4 scale, float4 dir);


	virtual void UpdateOff() {
		this->Off();
	}


	float GetLeft() {
		return GetPosition().ix() - GetScale().hix();
	}

	float GetRight() {
		return GetPosition().ix() + GetScale().hix();
	}

	float GetTop() {
		return GetPosition().iy() - GetScale().hiy();
	}

	float GetBottom() {
		return GetPosition().iy() + GetScale().hiy();
	}

	void SetInBox(bool b) {
		InBox = b;
	}

	bool GetInBox() {
		return InBox;
	}

	ITEMTYPE GetItemType() {
		return ItemType_;
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
	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* ItemRenderer_ = nullptr;
	GameEngineCollision* ItemCollider_ = nullptr;
	bool MouseHoldItem_ = false;
	ITEMTYPE ItemType_ = ITEMTYPE::ITEM;

private:
	bool InMouse;
	bool InBox;

};

