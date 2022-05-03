#include "MineLevel.h"
#include "MoveFlag.h"
#include "GameData.h"
#include "TileData.h"
#include <GameEngineBase/GameEngineTime.h>


MineLevel::MineLevel() 
{
	SetName("MineLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

MineLevel::~MineLevel() 
{
}

void MineLevel::Loading()
{

}

void MineLevel::Update()
{
}

void MineLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}

	BackGroundFront_->GetRenderer()->SetImage("MineStartFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ MINE_SIZE_WEIGHT / 2, MINE_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("MineStartBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ MINE_SIZE_WEIGHT / 2,  MINE_SIZE_HEIGHT / 2 });

	FlowingFlower_ = CreateActor<FlowingFlower>(static_cast<int>(PLAYLEVEL::EFFECT));
	//FlowingFlower_->SetMax({ BUSSTOP_SIZE_WEIGHT, BUSSTOP_SIZE_HEIGHT });
	FlowingFlower_->SetMaxFocusPlayer(true);

	//	Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
}

void MineLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
		PlayerHPFrame::MainPlayerHPFrame->NextLevelOn();

	}
}

void MineLevel::LoadMapObject()
{
	char MapOject[MINE_CHIP_NUM_Y][MINE_CHIP_NUM_X] = {
		#include "Map/Mine.txt"

	};

	for (int y = 0; y < MINE_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < MINE_CHIP_NUM_X; x++)
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
			int ChangeIndex = Index.X + (Index.Y * MINE_CHIP_NUM_Y);


			switch (TileState_)
			{

			case TILE_LIST::MOVE_FOREST:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveBackForest");

				break;

			case TILE_LIST::MINE_FLOOR:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveMinePoint");

				break;

			default:
				break;

			}



		}
	}
}
