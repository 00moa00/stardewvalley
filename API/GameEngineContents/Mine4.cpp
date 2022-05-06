#include "Mine4.h"

#include "MoveFlag.h"
#include "GameData.h"
#include "TileData.h"
#include "Block.h"
#include "SmallStone.h"
#include <GameEngineBase/GameEngineTime.h>

Mine4::Mine4() 
{
	SetName("Mine4");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

Mine4::~Mine4() 
{
}

void Mine4::Loading()
{
}

void Mine4::Update()
{
}

void Mine4::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}


	BackGroundFront_->GetRenderer()->SetImage("Mine4_Front.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ MINEFLOOR_SIZE_WEIGHT / 2, MINEFLOOR_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("Mine4_Back.bmp");
	BackGround_->GetRenderer()->SetPivot({ MINEFLOOR_SIZE_WEIGHT / 2,  MINEFLOOR_SIZE_HEIGHT / 2 });

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
}

void Mine4::LevelChangeEnd(GameEngineLevel* _NextLevel)
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

void Mine4::LoadMapObject()
{
	char MapOject[MINEFLOOR_CHIP_NUM_Y][MINEFLOOR_CHIP_NUM_X] = {
#include "Map/Mine4.txt"

	};

	for (int y = 0; y < MINEFLOOR_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < MINEFLOOR_CHIP_NUM_X; x++)
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
			int ChangeIndex = Index.X + (Index.Y * MINEFLOOR_CHIP_NUM_Y);


			switch (TileState_)
			{

			case TILE_LIST::MOVE_MINE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveMine");

				break;

			case TILE_LIST::MINE_FLOOR:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveMinePoint");
				ThisIter->second->CreateSubCollision("MapObject", { 48, 48 });
				ThisIter->second->ChnageImageFile("MineMove.bmp");

				break;

			case TILE_LIST::BLOCK:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<Block>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);

				break;
			case TILE_LIST::STONE0:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::STONE0);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::STONE0);

				break;
			case TILE_LIST::STONE1:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::STONE1);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::STONE1);
				
				break;
			case TILE_LIST::STONE2:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::STONE2);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::STONE2);
				
				break;
			case TILE_LIST::STONE3:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::STONE3);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::STONE3);
				
				break;
			case TILE_LIST::STONE4:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::STONE4);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::STONE4);
				
				break;
			case TILE_LIST::STONE5:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::STONE5);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::STONE5);
			
				break;
			case TILE_LIST::COPPER:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::COPPER);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::COPPER_STONE);

				break;
			case TILE_LIST::RUBY:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::RUBY);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::RUBY_STONE);
				
				break;
			case TILE_LIST::AMETHYST:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::AMETHYST);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::AMETHYST_STONE);

				break;
			case TILE_LIST::AQUAMARINE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetPosition(pos);
				ThisIter->second->GetCollision()->SetScale({ 40, 10 });
				ThisIter->second->GetCollision()->SetPivot({ 0, -10 });
				ThisIter->second->SetStoneType(STONETYPE::AQUAMARINE);

				ThisIter->second->ChnageImageFileAndIndex("springobjects.bmp", ITEM::AQUAMARINE_STONE);

				break;
			default:
				break;

			}

		}
	}

	Player::MainPlayer->CopyList(MapObject_);
	MapObject_.clear();
}
