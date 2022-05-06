#include "SaloonLevel.h"

#include "GameData.h"

#include "MoveFlag.h"
#include "ShopFlag.h"
#include "Gus.h"
#include "Block.h"

SaloonLevel::SaloonLevel() 
	:
	Shop_(nullptr)
{
	SetName("SaloonLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

SaloonLevel::~SaloonLevel() 
{
}

void SaloonLevel::Loading()
{
	/*if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(PLAYLEVEL::PLAYER));
	}

	if (nullptr == Inventory::MainInventory)
	{
		Inventory::MainInventory = CreateActor<Inventory>(static_cast<int>(PLAYLEVEL::INVENTORY));
	}

	if (nullptr == MainUI::MainMainUI)
	{
		MainUI::MainMainUI = CreateActor<MainUI>(static_cast<int>(PLAYLEVEL::MAINUI));
	}

	if (nullptr == PlayerEnergyFrame::MainPlayerEnergyFrame)
	{
		PlayerEnergyFrame::MainPlayerEnergyFrame = CreateActor<PlayerEnergyFrame>(static_cast<int>(PLAYLEVEL::ENERGYFRAME));
	}

	if (nullptr == Shop::MainShop)
	{
		Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
	}*/

	//if (nullptr == Shop::MainShop)
	//{
	//	Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
	//}




}

void SaloonLevel::Update()
{
}

void SaloonLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (nullptr == Shop::MainShop)
	{
		Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
		//Shop::MainShop->Off();
	}

	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}

	BackGroundFront_->GetRenderer()->SetImage("Saloon_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ SALOON_SIZE_WEIGHT / 2, SALOON_SIZE_HEIGHT / 2 });
	BackGroundFront_->SetOrder(static_cast<int>(PLAYLEVEL::BACKGROUND_FRONT));

	BackGround_->GetRenderer()->SetImage("Saloon_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ SALOON_SIZE_WEIGHT / 2, SALOON_SIZE_HEIGHT / 2 });
	BackGround_->SetOrder(static_cast<int>(PLAYLEVEL::BACKGROUND));


	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
	YSortOn(static_cast<int>(PLAYLEVEL::PLAYER));

}

void SaloonLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
		PlayerHPFrame::MainPlayerHPFrame->NextLevelOn();
	}

	if (nullptr != Shop::MainShop )
	{
		Shop::MainShop->Death();
		Shop::MainShop = nullptr;
	}

}

void SaloonLevel::LoadMapObject()
{
	char MapOject[SALOON_CHIP_NUM_Y][SALOON_CHIP_NUM_X] = {
		#include "Map/Saloon.txt"

	};


	for (int y = 0; y < SALOON_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < SALOON_CHIP_NUM_X; x++)
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
			int ChangeIndex = Index.X + (Index.Y * SALOON_CHIP_NUM_Y);


			switch (TileState_)
			{

			case TILE_LIST::GUS:

				NpcList_.insert(std::make_pair("Gus", CreateActor<Gus>((int)PLAYLEVEL::PLAYER)));
				NpcIter = --NpcList_.end();
				NpcIter->second->SetPosition(pos);
				NpcIter->second->SetPrevPos(pos);

				break;


			case TILE_LIST::SHOP_FLAG:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<ShopFlag>((int)PLAYLEVEL::OBJECT)));
				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				break;


			case TILE_LIST::BLOCK:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<Block>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);

				break;

			case TILE_LIST::MOVE_TOWN:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);

				ThisIter->second->CreateMoveFlag("MoveTown");

				break;


			default:
				break;

			}

		}
	}

	Player::MainPlayer->CopyList(MapObject_);
	Player::MainPlayer->CopyList(NpcList_);

}
