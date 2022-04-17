#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>

#include "RendererData.h"
#include "ItemCode.h"
#include "ToolData.h"
#include "Font.h"
#include "CropsData.h"
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

enum class MOVE
{
	INIT,
	Y_UP,
	Y_DOWN
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
	Items& operator=(Items&& _Other) noexcept = delete;


protected:
	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* ItemRenderer_;
	GameEngineCollision* ItemCollider_;
	GameEngineCollision* MapItemCollider_;

	Font* Font_;

	ITEMTYPE ItemType_;
	TOOLTYPE ToolType_;
	ITEM_STATE ItemState_;
	MOVE State_;

	int Count_;
	int FileIndex_;

	float4 ItemPosition_;
	float4 ItemSpeed_;
	float4 Gravity_;
	float4 targetPos_;
	float4 TransformPos_;
	float4 Normal_;


	bool MouseHoldItem_;
	bool isPossibleHand_;
	bool isDeath_;
	bool MoveFlag_;

	std::string Name_;
	std::string FilePath_;
	

private:

	bool InMouse;
	bool InBox;

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
	void MoveToPlayer();

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

	int GetFileIndex()
	{
		return FileIndex_;
	}

	bool IsDeath()
	{
		return isDeath_;
	}


	bool GetInBox()
	{
		return InBox;
	}

	bool GetisPossibleHand()
	{
		return isPossibleHand_;
	}

	ITEMTYPE GetItemType()
	{
		return ItemType_;
	}

	TOOLTYPE GetToolType()
	{
		return ToolType_;
	}

	const std::string& GetFilePath()
	{
		return FilePath_;
	}

	const std::string& GetItemNameConstRef()
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

	void SetMoveFlag(bool _flag)
	{
		MoveFlag_ = _flag;
	}

	void SetDeath(bool _flag)
	{
		isDeath_ = _flag;
	}

	void SetRenderer(GameEngineRenderer& _Renderer) {

		ItemRenderer_ = &_Renderer;
	}


	void AddCount()
	{
		++Count_;
	}

	void SetInBox(bool _b)
	{
		InBox = _b;
	}

	void SetItemStateAddItem()
	{
		++Count_;
		ItemState_ = ITEM_STATE::ADDITEM;
	}

	void SetItemName(std::string _Name)
	{
		Name_ = _Name;
	}

	void SetFilePath(const std::string& _Path)
	{
		FilePath_ = _Path;
	}

	void SetFileIndex(int _FileIndex)
	{
		FileIndex_ = _FileIndex;
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

		return (MapItemCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect));
	}



};

