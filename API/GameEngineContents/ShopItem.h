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

// 설명 :
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

protected:
	GameEngineRenderer* ShopItemListRenderer_;
	GameEngineCollision* ShopItemListCollider_;

	int Index_;

private:


public:

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


//자료구조는 맵
//제어 : 가장 첫번째 인덱스(멥)가 지정인덱스(ㅈ위치)와 같다면 스크롤을 멈춘다
//렌더 : 인덱스(멤버변수) 1~4번만 렌더링

