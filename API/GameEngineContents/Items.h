#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "RendererData.h"
#include "ItemCode.h"
#include "ToolData.h"
#include "Font.h"
#include "Crops.h"
//#include "Player.h"

enum class SEEDTYPE
{
	NONE,
	PARSNIP_SEED,
	BEAN_SEED,
	CAULIFLOWER_SEED,
	POTATO_SEED,
	TULIP_SEED,
	KALE_SEED,
	JAZZ_SEED,
};

enum class ITEMTYPE
{
	ITEM,
	MAPOBJECT,
	TREE,
	STONE,
	WOOD,
	TOOL,
	GETITEM,
	FLAG,
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
	SUBITEM
};

enum class MOVE
{
	INIT,
	STOP,
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

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

public:
	virtual void TreeOff();
	virtual void SetCrushAnimation();
	virtual void SetInitAnimation();

	virtual void AddItemCount();
	virtual void SubItemCount();
	virtual void SetItemCount(int _Count);

	virtual void DropItemInMap();
	virtual Crops* CreateCrops();

	virtual void GetItemAndAddInventory();

	virtual void UpdateOff()
	{
		this->Off();
	}

	virtual void UpdateOn()
	{
		this->On();
	}



protected:
	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* ItemRenderer_;
	GameEngineCollision* ItemCollider_;

	GameEngineRenderer* SubRenderer;

	GameEngineRandom RandomItemCount;
	GameEngineRandom RandomItemPosX;
	GameEngineRandom RamdomItemPosY;


	SEEDTYPE SeedType_;
	ITEMTYPE ItemType_;
	TOOLTYPE ToolType_;
	ITEM_STATE ItemState_;
	MOVE State_;

	//GameEngineRandom RamdomSpeed_;

	int SellPrice_;
	int ItemCount_;
	int Damage_;
	float Speed_;

	float4 ItemPosition_;
	float4 ItemSpeed_;
	float4 Gravity_;
	float4 targetPos_;
	float4 TransformPos_;
	float4 Normal_;


	bool MouseHoldItem_;
	bool isPossibleHand_;
	bool isMapItemDeath_;
	bool isMove_;

	std::string ItemName_;
	std::string FileName_;
	int FileIndex_;


private:

	bool InMouse;
	bool InBox;

protected:


public:
	bool ItemCheck(const float4 pos, const float4 scale);
	void MoveToPlayer();
	//================================
	//     Getter
	//================================

	GameEngineCollision* GetCollision() 
	{

		return ItemCollider_;
	}

	GameEngineRenderer* GetRenderer() 
	{
		return ItemRenderer_;
	}

	GameEngineRenderer* GetSubRenderer()
	{
		return SubRenderer;
	}

	int GetItemCount()
	{
		return ItemCount_;
	}

	int GetSellPrice()
	{
		return SellPrice_;
	}

	int GetDamage()
	{
		return Damage_;
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



	bool IsMapItemDeath()
	{
		return isMapItemDeath_;
	}


	bool GetInBox()
	{
		return InBox;
	}

	bool GetisPossibleHand()
	{
		return isPossibleHand_;
	}

	SEEDTYPE GetSeedType()
	{
		return SeedType_;
	}

	ITEMTYPE GetItemType()
	{
		return ItemType_;
	}

	TOOLTYPE GetToolType()
	{
		return ToolType_;
	}

	const std::string& GetFileName()
	{
		return FileName_;
	}

	const std::string& GetItemNameConstRef()
	{
		return ItemName_;
	}

	bool MouseHoldItem()
	{
		return MouseHoldItem_;
	}

	//================================
	//    Setter
	//================================


	void SubDamage()
	{
		if (Damage_ > 0)
		{
			--Damage_;
		}
	}

	void SetDamage(int _Damage)
	{
		Damage_ = _Damage;
	}

	void SetMoveFlag(bool _flag)
	{
		isMove_ = _flag;
	}

	void SetMapItemDeath(bool _flag)
	{
		isMapItemDeath_ = _flag;
	}

	void SetRenderer(GameEngineRenderer& _Renderer) {

		ItemRenderer_ = &_Renderer;
	}



	void SetInBox(bool _b)
	{
		InBox = _b;
	}


	void SetItemName(std::string _Name)
	{
		ItemName_ = _Name;
	}

	void SetFileName(const std::string& _Name)
	{
		FileName_ = _Name;
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


	template<typename Actor>
	Actor* CreateDropItemActor()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SEED));
		return Item;
	}

};

