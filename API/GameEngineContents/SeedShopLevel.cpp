#include <GameEngineBase/GameEngineTime.h>
#include "SeedShopLevel.h"

#include "GameData.h"
#include "Block.h"
#include "MoveFlag.h"
#include "ShopFlag.h"
#include "Pierre.h"

SeedShopLevel::SeedShopLevel()
	:
	Shop_(nullptr)
	
{

	SetName("SeedShopLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

SeedShopLevel::~SeedShopLevel()
{

}

void SeedShopLevel::Loading()
{
	//if (nullptr == Player::MainPlayer)
	//{
	//	Player::MainPlayer = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	//}

	//if (nullptr == Inventory::MainInventory)
	//{
	//	Inventory::MainInventory = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);
	//}

	//if (nullptr == MainUI::MainMainUI)
	//{
	//	MainUI::MainMainUI = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	//}
	// 

	//if (nullptr == Shop::MainShop)
	//{
	//	Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
	//}



}

void SeedShopLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (nullptr == Shop::MainShop)
	{
		Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
	}

	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}
	//Shop_ = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));

	BackGroundFront_->GetRenderer()->SetImage("SeedShop_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ SHOP_SIZE_WEIGHT / 2, SHOP_SIZE_HEIGHT / 2 });
	BackGroundFront_->SetOrder(static_cast<int>(PLAYLEVEL::BACKGROUND_FRONT));

	BackGround_->GetRenderer()->SetImage("SeedShop_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ SHOP_SIZE_WEIGHT / 2, SHOP_SIZE_HEIGHT / 2 });
	BackGround_->SetOrder(static_cast<int>(PLAYLEVEL::BACKGROUND));
	
	
	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
	//YSortOn(static_cast<int>(PLAYLEVEL::PLAYER));

	//BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	//Time = 5.0f;
}

void SeedShopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
		PlayerHPFrame::MainPlayerHPFrame->NextLevelOn();
	}

	if (nullptr != Shop::MainShop)
	{
		Shop::MainShop->Death();
		Shop::MainShop = nullptr;

	}
	//Player::MainPlayer->SetisShopping(false);
	//Shop_->Death();
}



void SeedShopLevel::LoadMapObject()
{

	char MapOject[SHOP_CHIP_NUM_Y][SHOP_CHIP_NUM_X] = {
		#include "Map/SeedShop.txt"

	};


	for (int y = 0; y < SHOP_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < SHOP_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE * 0.5f,
			};

			TILE_LIST TileState_ = static_cast<TILE_LIST>(chip);
			std::map<int, Items*>::iterator ThisIter;
			std::map<std::string, Npc*>::iterator NpcIter;

			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * SHOP_CHIP_NUM_Y);


			switch (TileState_)
			{

			case TILE_LIST::PIERRE:

				NpcList_.insert(std::make_pair("Pierre", CreateActor<Pierre>((int)PLAYLEVEL::OBJECT)));
				NpcIter = --NpcList_.end();
				NpcIter->second->SetPosition(pos);
				break;

			case TILE_LIST::SHOP_FLAG:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<ShopFlag>((int)PLAYLEVEL::OBJECT)));
				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::MOVE_TOWN:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));
				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveTown");

				break;

			case TILE_LIST::BLOCK:
				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<Block>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);

				break;
			default:
				break;

			}

		}
	}

	 Player::MainPlayer->CopyList(MapObject_);
	 Player::MainPlayer->CopyList(NpcList_);

}


void SeedShopLevel::Update()
{

	//float4 NextPos = Player_->GetPosition() + (float4::RIGHT *GameEngineTime::GetDeltaTime() * 150.f);
	//float4 CheckPos = NextPos + float4(0.0f, 20.0f);
	//std::list<Items*>::iterator Iter;

	//Time -= GameEngineTime::GetDeltaTime();



	//if (0 >= Time)
	//{
	//	//	BgmPlayer.Stop();
	//}



}
