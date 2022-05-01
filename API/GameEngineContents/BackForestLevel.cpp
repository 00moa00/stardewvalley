#include "BackForestLevel.h"
#include "MoveFlag.h"
#include "GameData.h"
#include "TileData.h"
#include "Block.h"
#include <GameEngineBase/GameEngineTime.h>

BackForestLevel::BackForestLevel() 
	:
	FlowingFlower_(nullptr)
{
	SetName("BackForestLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

BackForestLevel::~BackForestLevel() 
{
}

void BackForestLevel::Loading()
{

}

void BackForestLevel::Update()
{
}

void BackForestLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}

	BackGroundFront_->GetRenderer()->SetImage("BacKForest_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ FOREST_SIZE_WEIGHT / 2, FOREST_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("BacKForest_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ FOREST_SIZE_WEIGHT / 2,  FOREST_SIZE_HEIGHT / 2 });

	FlowingFlower_ = CreateActor<FlowingFlower>(static_cast<int>(PLAYLEVEL::EFFECT));
	//FlowingFlower_->SetMax({ BUSSTOP_SIZE_WEIGHT, BUSSTOP_SIZE_HEIGHT });
	FlowingFlower_->SetMaxFocusPlayer(true);

//	Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
}

void BackForestLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
	}
}

void BackForestLevel::LoadMapObject()
{
	char MapOject[FOREST_CHIP_NUM_Y][FOREST_CHIP_NUM_X] = {
		#include "Map/BackForest.txt"

	};

	for (int y = 0; y < FOREST_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < FOREST_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE * 0.5f,
			};

			TILE_LIST TileState_ = static_cast<TILE_LIST>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FOREST_CHIP_NUM_Y);


			switch (TileState_)
			{

			case TILE_LIST::MOVE_MINE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveMine");

				break;

			case TILE_LIST::MOVE_FARM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveFarm");

				break;

			case TILE_LIST::BLOCK:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<Block>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);

				break;
			default:
				break;

			}



		}
	}

	Player::MainPlayer->CopyList(MapObject_);
	MapObject_.erase(MapObject_.begin(), MapObject_.end());
}
