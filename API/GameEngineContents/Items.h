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

	Font* Font_;

	ITEMTYPE ItemType_;
	TOOLTYPE ToolType_;
	ITEM_STATE ItemState_;

	int Count_;
	int FileIndex_;

	bool MouseHoldItem_;
	bool isPossibleHand_;

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

	//================================
	//     Getter
	//================================

	GameEngineCollision* GetCollision() {

		return ItemCollider_;
	}
	GameEngineRenderer* GetRenderer() {

		return ItemRenderer_;
	}
	GameEngineRenderer& GetRendererLef() {

		return *ItemRenderer_;
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

		return (ItemCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect));
	}

};

