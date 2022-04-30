#include "SaloonLevel.h"

#include "GameData.h"

#include "MoveTown.h"
#include "ShopFlag.h"


SaloonLevel::SaloonLevel() 
	:
	Shop_(nullptr)
{
	SetName("ShopLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

SaloonLevel::~SaloonLevel() 
{
}

void SaloonLevel::Loading()
{
	if (nullptr == Shop::MainShop)
	{
		Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
	}


	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}
}

void SaloonLevel::Update()
{
}

void SaloonLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void SaloonLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void SaloonLevel::LoadMapObject()
{
}
