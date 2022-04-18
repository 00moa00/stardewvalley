#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>

#include "RendererData.h"


enum class SHOP_LIST
{
	PARSNIPSEEDS,
	BEANSTARTER,
	CAULIFLOWERSEEDS,
	PATAPOSEEDS,
	TULIPBULB,
	KALESEEDS,
	JAZZSEEDS,
	PARSNIP,
	DANDELION,
	DAFFODIL
};

// ���� :
class ShopItem : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;

public:

	virtual void InventoryNewItem() = 0;

private:

protected:

	GameEngineRenderer* ShopItemListRenderer_;
	GameEngineCollision* ShopItemListCollider_;
	std::vector<GameEngineCollision*> ColList;

	int Index_;

public:

	bool MouseInItem()
	{
		return (ShopItemListCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	//================================
	//     Getter
	//================================

	int GetIndex()
	{
		return Index_;
	}

	//================================
	//    Setter
	//================================

	void SetIndex(int _Index)
	{
		Index_ = _Index;
	}

	void AddIndex()
	{
		++Index_;
	}

	void SubIndex()
	{
		--Index_;
	}

};


//�ڷᱸ���� ��
//���� : ���� ù��° �ε���(��)�� �����ε���(����ġ)�� ���ٸ� ��ũ���� �����
//���� : �ε���(�������) 1~4���� ������

