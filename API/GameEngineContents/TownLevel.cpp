#include <GameEngineBase/GameEngineTime.h>

#include "TownLevel.h"

#include "GameData.h"

#include "Block.h"
#include "MoveBusStop.h"
#include "MoveShop.h"
#include "Lewis.h"
#include "Penny.h"
#include "TreeBottom.h"

TownLevel::TownLevel()
	:
	Iter(MapObject_.begin())

{

	SetName("TownLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

TownLevel::~TownLevel()
{

}

void TownLevel::Loading()
{
	if (nullptr == Player::MainPlayer)
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

	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}
}

void TownLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

	BackGroundFront_->GetRenderer()->SetImage("TownFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ TOWN_SIZE_WEIGHT / 2, TOWN_SIZE_HEIGHT / 2 });
	BackGroundFront_->SetOrder(static_cast<int>(PLAYLEVEL::BACKGROUND_FRONT));

	BackGround_->GetRenderer()->SetImage("TownBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ TOWN_SIZE_WEIGHT / 2, TOWN_SIZE_HEIGHT / 2 });

	//BackGround_->DirtTileMap_.TileRangeSetting(TOWN_CHIP_NUM_X, TOWN_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	//BackGround_->WetTileMap_.TileRangeSetting(TOWN_CHIP_NUM_X, TOWN_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });


	Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);
	Player::MainPlayer->SetWetTileMap(&BackGround_->WetTileMap_);

	//BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	//Time = 5.0f;
	YSortOn(static_cast<int>(PLAYLEVEL::PLAYER));
	
	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();

}

void TownLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();

	}
}



void TownLevel::LoadMapObject()
{

	char MapOject[TOWN_CHIP_NUM_Y][TOWN_CHIP_NUM_X] = {

	#include "Map/Town.txt"

	};


	for (int y = 0; y < TOWN_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < TOWN_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE,
			};

			TILE_LIST TileState_ = static_cast<TILE_LIST>(chip);
			std::map<int, Items*>::iterator ThisIter;
			std::map<std::string, Npc*>::iterator NpcIter;

			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * TOWN_CHIP_NUM_Y);


			switch (TileState_)
			{


			//case TILE_LIST::BLOCK:

			//	MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<Block>((int)PLAYLEVEL::OBJECT)));
			//	ThisIter = --MapObject_.end();
			//	ThisIter->second->SetPosition(pos);

			//	break;

			case TILE_LIST::LEWIS:

				NpcList_.insert(std::make_pair("Lewis", CreateActor<Lewis>((int)PLAYLEVEL::PLAYER)));
				NpcIter = --NpcList_.end();
				NpcIter->second->SetPosition(pos);
				break;
			case TILE_LIST::PENNY:

				NpcList_.insert(std::make_pair("Penny", CreateActor<Penny>((int)PLAYLEVEL::PLAYER)));
				NpcIter = --NpcList_.end();
				NpcIter->second->SetPosition(pos);

				break;
			case TILE_LIST::MOVE_SHOP:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveShop>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);

				break;
			case TILE_LIST::MOVE_BUSSTOP:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveBusStop>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
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


void TownLevel::Update()
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
