#include "BusStopLevel.h"
#include "MoveTown.h"
#include "MoveFarm.h"
#include "GameData.h"
#include "TileData.h"
#include <GameEngineBase/GameEngineTime.h>
BusStopLevel::BusStopLevel() 
	:
	Iter(MapObject_.begin())
{

	SetName("BusStopLevel");

}

void BusStopLevel::Loading()
{
	//if (nullptr == Player::MainPlayer)
	//{
	//	Player::MainPlayer = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	//}

	//if (nullptr == Inventory::MainInventory)
	//{
	//	Inventory::MainInventory = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);
	//}

	//if (nullptr == Inventory::MainInventory)
	//{
	//	MainUI::MainMainUI = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	//}

	if(MapObject_.empty()== true)
	{
		LoadMapObject();
	}

}

void BusStopLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

	BackGroundFront_->GetRenderer()->SetImage("BusStop_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ BUSSTOP_SIZE_WEIGHT / 2, BUSSTOP_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("BusStop_Back.bmp");

	BackGround_->GetRenderer()->SetPivot({ BUSSTOP_SIZE_WEIGHT / 2,  BUSSTOP_SIZE_HEIGHT / 2 });



	Player::MainPlayer->SetPosition({ (1300.f), 1140.f});
	Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);

}

void BusStopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
	}

}

BusStopLevel::~BusStopLevel() 
{
}



void BusStopLevel::Update()
{

}



void BusStopLevel::LoadMapObject()
{


	char MapOject[BUSSTOP_CHIP_NUM_Y][BUSSTOP_CHIP_NUM_X] = {
	#include "Map/Busstop.txt"

	};


	for (int y = 0; y < BUSSTOP_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < BUSSTOP_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE,
			};

			BUSSTOP_TILE TileState_ = static_cast<BUSSTOP_TILE>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);


			switch (TileState_)
			{
		
			case BUSSTOP_TILE::MOVE_TOWN:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveTown>((int)PLAYLEVEL::OBJECT)));


				break;
		
			case BUSSTOP_TILE::MOVE_FARM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFarm>((int)PLAYLEVEL::OBJECT)));
				break;
		
			default:
				break;

			}

			ThisIter = --MapObject_.end();
			ThisIter->second->SetPosition(pos);


		}
	}
	//Player_->CopyList(MapObject_);

}
