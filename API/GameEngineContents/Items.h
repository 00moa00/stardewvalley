#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>

#include "ItemCode.h"
#include "ToolData.h"
#include "Font.h"
//#include "Player.h"

// 설명 :

enum class ITEMTYPE
{

	ITEM,
	OBJECT,
	TOOL,
	BLOCK,

};

enum class TOOLTYPE 
{

	OTHER,
	HOE,
	WATTERING_CAN,
	AXE,
	PICKAXE

};

enum class ITEM_STATE
{
	INIT,
	ADDITEM,
};


class Items : public GameEngineActor
{
public:


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

	GameEngineRenderer* ItemRenderer_;
	GameEngineCollision* ItemCollider_;
	bool MouseHoldItem_;
	ITEMTYPE ItemType_;
	TOOLTYPE ToolType_;

private:

	bool InMouse;
	bool InBox;

	int Count_;

	std::string Name_;

	Font* Font_;

	ITEM_STATE ItemState_;

protected :

	virtual void UpdateOff()
	{
		this->Off();
	}


private:
	void Start() override;
	void Update() override;

public :

	bool IsWall(const float4 pos, const float4 scale, float4 dir);

	//================================
	//     Getter
	//================================

	GameEngineCollision* GetCollision() {

		return ItemCollider_;
	}
	GameEngineRenderer* GetRenderer() {

		return ItemRenderer_;
	}


	int GetLeft()
	{
		return GetPosition().ix() - GetScale().hix();
	}

	int GetRight()
	{
		return GetPosition().ix() + GetScale().hix();
	}

	int GetTop()
	{
		return GetPosition().iy() - GetScale().hiy();
	}

	int GetBottom()
	{
		return GetPosition().iy() + GetScale().hiy();
	}

	bool GetInBox()
	{
		return InBox;
	}

	ITEMTYPE GetItemType()
	{
		return ItemType_;
	}

	TOOLTYPE GetToolType()
	{
		return ToolType_;
	}

	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	bool MouseHoldItem()
	{
		return MouseHoldItem_;
	}

	//================================
	//    Setter
	//================================

	void SetInBox(bool _b)
	{
		InBox = _b;
	}

	void SetItemState(ITEM_STATE _state)
	{
		ItemState_ = _state;
	}

	inline void SetName(std::string _Name)
	{
		Name_ = _Name;
	}




	//------< 마우스, 충돌 관련 >------------------------------------------------------------------


	bool MouseOver()
	{
		return (ItemCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool IteminItem() 
	{

		return (ItemCollider_->CollisionResult("Item", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	bool IteminBox() 
	{

		return (ItemCollider_->CollisionResult("Box", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool playerVSobject() 
	{

		return (ItemCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect));
	}

};

