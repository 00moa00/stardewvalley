#include "BusStopLevel.h"
#include "MoveTown.h"
#include "MoveFarm.h"
#include "GameData.h"
#include "TileData.h"
#include <GameEngineBase/GameEngineTime.h>
BusStopLevel::BusStopLevel() 
	:

	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),
	TileState_(TILE_COLL::INIT),
	MainUI_(nullptr),
	Iter(MapObject_.begin())
{

	SetName("BusStopLevel");

	//Inventory_ = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);

	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

void BusStopLevel::LevelChangeStart()
{

	BackGroundFront_->GetRenderer()->SetImage("BusStop_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ BUSSTOP_SIZE_WEIGHT / 2, BUSSTOP_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("BusStop_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ BUSSTOP_SIZE_WEIGHT / 2,  BUSSTOP_SIZE_HEIGHT / 2 });
	BackGround_->TileMap_.TileRangeSetting(BUSSTOP_CHIP_NUM_X, BUSSTOP_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });

	LoadMapObject();

	Player_->SetPosition({ (BUSSTOP_SIZE_WEIGHT/2), (BUSSTOP_SIZE_HEIGHT / 2)});
	Player_->SetTileMap(&BackGround_->TileMap_);

}

BusStopLevel::~BusStopLevel() 
{
}

void BusStopLevel::Loading()
{
}

void BusStopLevel::Update()
{
}



void BusStopLevel::LoadMapObject()
{


	char MapOject[BUSSTOP_CHIP_NUM_Y][BUSSTOP_CHIP_NUM_X] = {
	#include "Map/Busstop.txt";

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
			std::list<Items*>::iterator ThisIter;

			switch (TileState_)
			{
		
			case BUSSTOP_TILE::MOVE_TOWN:
				MapObject_.push_back(CreateActor<MoveTown>((int)PLAYLEVEL::OBJECT));

				break;
		
			case BUSSTOP_TILE::MOVE_FARM:
				MapObject_.push_back(CreateActor<MoveFarm>((int)PLAYLEVEL::OBJECT));

		
			default:
				break;

			}
			ThisIter = --MapObject_.end();
			(*ThisIter)->SetPosition(pos);


		}
	}

}
