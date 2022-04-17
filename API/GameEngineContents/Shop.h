#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

#include <map>

#include "ShopItem.h"

#include "TulipBulb_Shop.h"
#include "PatatoSeeds_Shop.h"
#include "ParsnipSeeds_Shop.h"
#include "Parsnip_Shop.h"
#include "KaleSeeds_Shop.h"
#include "JazzSeeds_Shop.h"
#include "Dandelion_Shop.h"
#include "Daffodil_Shop.h"
#include "CauliflowerSeeds_Shop.h"
#include "BeanStarter_Shop.h"


enum class SHOP_UPDATE
{
	SET_POS_INDEX,
	HIDE_ITME,
	INIT,
	SCROLL_UP,
	SCROLL_DOWN

};

// 설명 :
class Shop : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop();
	~Shop();

	// delete Function
	Shop(const Shop& _Other) = delete;
	Shop(Shop&& _Other) noexcept = delete;
	Shop& operator=(const Shop& _Other) = delete;
	Shop& operator=(Shop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

private:

	GameEngineRenderer* ShopRenderer_;

	std::map<int, ShopItem*> ShopItemList_;
	std::map<int, float4> ConstItmePos_;



	SHOP_UPDATE ShopUpdateState_;

public:

	void ShopOff();
	void ShopOn();

	template<typename Actor>
	void NewShopItem()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SHOP_ITEM_LIST));
		
		//기본 인덱스로 초기화
		int Index = Item->GetIndex();
		ShopItemList_.insert(std::make_pair(Index, Item));

	}

protected:

};

