#include "Mine2.h"
#include "MoveFlag.h"
#include "GameData.h"
#include "TileData.h"
#include "Block.h"
#include <GameEngineBase/GameEngineTime.h>
Mine2::Mine2() 
{
	SetName("Mine1");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

Mine2::~Mine2() 
{
}

void Mine2::Loading()
{
	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}
}

void Mine2::Update()
{
}

void Mine2::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	BackGroundFront_->GetRenderer()->SetImage("Mine2_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ MINEFLOOR_SIZE_WEIGHT / 2, MINEFLOOR_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("Mine2_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ MINEFLOOR_SIZE_WEIGHT / 2,  MINEFLOOR_SIZE_HEIGHT / 2 });

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
}

void Mine2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
	}
}

void Mine2::LoadMapObject()
{
	char MapOject[MINEFLOOR_CHIP_NUM_Y][MINEFLOOR_CHIP_NUM_X] = {
	#include "Map/Mine2.txt"

	};

	for (int y = 0; y < MINEFLOOR_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < MINEFLOOR_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE,
			};

			TILE_LIST TileState_ = static_cast<TILE_LIST>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * MINEFLOOR_CHIP_NUM_Y);


			switch (TileState_)
			{

			case TILE_LIST::MOVE_MINE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveMine");

				break;

			case TILE_LIST::MINE_FLOOR:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveMine3");
				ThisIter->second->ChnageImageFile("MineMove.bmp");

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
}
