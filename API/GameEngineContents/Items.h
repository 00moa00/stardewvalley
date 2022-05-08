#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>

#include "RendererData.h"
#include "ItemCode.h"
#include "ToolData.h"
#include "Font.h"
#include "Crops.h"
#include "ItemDataBox.h"
//#include "Player.h"


enum class OBJECTTYPE
{
	OTHER,
	ITEM,
	MAPOBJECT,
	TREE,
	STONE,
	WOOD,
	TOOL,
	GETITEM,
	SHIPPINGBOX,
	FOOD,
	DRINK,
	SEED,
	FLAG,
	BLOCK,
};

enum class ITEMTYPE
{
	OTHER,
	FARMING,
	GATHERING,
	FISHING,
	MINING,
	ETC
};

enum class SEEDTYPE
{
	OTHER,
	PARSNIP_SEED,
	BEAN_SEED,
	CAULIFLOWER_SEED,
	POTATO_SEED,
	TULIP_SEED,
	KALE_SEED,
	JAZZ_SEED,
};

enum class DRINKTYPE
{
	OTHER,
	SPEED_UP,
	SPEED_DOWN,
};

enum class TOOLTYPE 
{
	OTHER,
	HOE,
	WATTERING_CAN,
	AXE,
	PICKAXE,
	SWOARD
};

enum class STONETYPE
{
	OTHER,
	STONE0,
	STONE1,
	STONE2,
	STONE3,
	STONE4,
	STONE5,

	COPPER,
	RUBY,
	AMETHYST,
	AQUAMARINE,
};

enum class ITEM_STATE
{
	INIT,
	ANIMATION,
	SIDE_ANIMATION,
	MOVETOPLAYER
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
	virtual void DropItemInMap(STONETYPE _StoneType);


	virtual Crops* CreateCrops();

	virtual void ItemCollPlayer();
	virtual void ItemCollFalsePlayer();
	virtual void CreateMoveFlag(std::string _CollName);
	virtual void ChnageImageFile(std::string _FileName);
	virtual void ChnageImageFileAndIndex(std::string _FileName, ITEM _index);
	virtual void CreateSubCollision(std::string _CollName, float4 _Size);


	virtual void UpdateOff()
	{
		this->Off();
	}

	virtual void UpdateOn()
	{
		this->On();
	}

	virtual void SetMoveDir(float4 _Dir)
	{
		MoveDir_ = _Dir;
	}

protected:
	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* ItemRenderer_;
	GameEngineCollision* ItemCollider_;

	GameEngineRenderer* SubRenderer_;
	GameEngineCollision* SubCollider_;

	GameEngineRandom RandomItemCount;


	GameEngineRandom RandomItemPosX;
	GameEngineRandom RamdomItemPosY;


	SEEDTYPE SeedType_;
	OBJECTTYPE ObjectType_;
	TOOLTYPE ToolType_;
	DRINKTYPE DrinkType_;
	STONETYPE StoneType_;
	ITEMTYPE ItemType_;
	ITEM_STATE ItemState_;
	MOVE State_;

	int Power_;
	int Damage_;			//맵 오브젝트 데미지
	int SellPrice_;			//파는 금액
	int ItemCount_;			//아이템 개수
	int FileIndex_;			//핸드아이템 전달 인덱스
	int RamdomDir_;			//맵 팝업 아이템의 랜덤 방향 정하는 용
	int AddEnery_;			//음식 옵션 - 에너지 증가
	int AddHP_;				//음식 옵션 - HP증가
	int ChangeSpeed_;		//드링크 마시면 생기는 속도 관련 버프/ 디버프
	//int Damage_;			//데미지

	float ChangeTime_;		//드링크 버프/ 디버프 시간

	float4 ItemPosition_;
	float4 ItemSpeed_;
	float4 MoveDir_;
	float4 PrePosition_;
	float4 Normal_;

	bool MouseHoldItem_;
	bool isPossibleHand_;
	bool isMapItemDeath_;
	bool isMove_;
	bool InMouse;
	bool InBox;

	std::string ItemName_;
	std::string FileName_;


private:



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
		return SubRenderer_;
	}

	int GetPower()
	{
		return Power_;
	}

	int GetDrinkChangeSpeed()
	{
		return ChangeSpeed_;
	}

	int GetAddEnergy()
	{
		return AddEnery_;
	}

	int GetAddHP()
	{
		return AddHP_;
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

	float GetChangeSpeedTime()
	{
		return ChangeTime_;
	}

	bool GetInBox()
	{
		return InBox;
	}

	bool GetisPossibleHand()
	{
		return isPossibleHand_;
	}

	STONETYPE GetStoneType()
	{
		return StoneType_;
	}

	DRINKTYPE GetDrinkType()
	{
		return DrinkType_;
	}

	SEEDTYPE GetSeedType()
	{
		return SeedType_;
	}

	OBJECTTYPE GetObjectType()
	{
		return ObjectType_;
	}

	TOOLTYPE GetToolType()
	{
		return ToolType_;
	}

	ITEMTYPE GetItemType()
	{
		return ItemType_;
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

	void SetStoneType(STONETYPE _Type)
	{
		StoneType_ = _Type;
	}

	void CreateItemCollision(std::string _CollName, float4 _Size)
	{
		ItemCollider_ = CreateCollision(_CollName, _Size);

	}

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

	void SetInMouse(bool _b)
	{
		InMouse = _b;
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




};

