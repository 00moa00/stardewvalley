#include "MyFarmLevel.h"
#include "GameData.h"

#include "SmallStone.h"
#include "SmallWood1.h"
#include "SmallWood2.h"
#include "TreeTop.h"
#include "TreeBottom.h"

#include "PlayerHouse.h"
#include "ShippingBox.h"
#include "Block.h"

#include "MoveHouse.h"
#include "MoveBusStop.h"
#include "MoveForest.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>


MyFarmLevel::MyFarmLevel()
	:
	Iter(MapObject_.begin()),
	Time(0.f)
	
{
	SetName("MyFarmLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

MyFarmLevel::~MyFarmLevel()
{

}

void MyFarmLevel::Loading()
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	}

	if (nullptr == Inventory::MainInventory)
	{
		Inventory::MainInventory = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);
	}

	if (nullptr == MainUI::MainMainUI)
	{
		MainUI::MainMainUI = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	}

	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}

}

void MyFarmLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
	BackGroundFront_->GetRenderer()->SetImage("FarmFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("FarmBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

	BackGround_->DirtTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	BackGround_->WetTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	BackGround_->GetRenderer()->CameraEffectOn();

	
	Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);
	Player::MainPlayer->SetWetTileMap(&BackGround_->WetTileMap_);
	Player::MainPlayer->Renderer()->CameraEffectOn();

	//BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	//Time = 5.0f;
}

void MyFarmLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
	}

}

void MyFarmLevel::LoadMapObject()
{

    char MapOject[FARM_CHIP_NUM_Y][FARM_CHIP_NUM_X] = 
	{
		 #include "Map/Farm.txt"
    };
	 

    for (int y = 0; y < FARM_CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < FARM_CHIP_NUM_X; x++)
        {
            const char chip = MapOject[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE + CHIP_SIZE * 0.5f,
                y * CHIP_SIZE + CHIP_SIZE * 0.5f,
            };

			FARM_TILE TileState_ = static_cast<FARM_TILE>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

			switch (TileState_)
			{
			case FARM_TILE::MAPLE_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetItemName("Maple_Tree");

				break;

			case FARM_TILE::FINE_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetItemName("Fine_Tree");

				break;

			case FARM_TILE::OAK_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetItemName("Oak_Tree");

				break;

			case FARM_TILE::SMALL_STONE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));
			
				break;

			case FARM_TILE::BIG_STONE:
				break;
			case FARM_TILE::SMALL_WOOD1:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallWood1>((int)PLAYLEVEL::OBJECT)));
		
				break;

			case FARM_TILE::SMAA_WOOD2:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallWood2>((int)PLAYLEVEL::OBJECT)));

				break;

			case FARM_TILE::MIDDLE_WOOD:
				break;
			case FARM_TILE::BIG_WOOD:
				break;
			case FARM_TILE::WEED1:
				break;
			case FARM_TILE::WEED2:
				break;

			case FARM_TILE::SHIPPING_BOX:
				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<ShippingBox>((int)PLAYLEVEL::OBJECT)));

				break;


			case FARM_TILE::MOVE_FOREST:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveForest>((int)PLAYLEVEL::OBJECT)));

				break;


			case FARM_TILE::MOVE_BUSSTOP:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveBusStop>((int)PLAYLEVEL::OBJECT)));

				break;

			case FARM_TILE::MOVE_HOUSE :

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveHouse>((int)PLAYLEVEL::OBJECT)));

				break;

		

			case FARM_TILE::BLOCK :

				break;
			default:
				break;
			
			}
			ThisIter = MapObject_.find(ChangeIndex);
			ThisIter->second->SetPosition(pos);
			
     
        }
    }

	Player::MainPlayer->CopyList(MapObject_);
	MapObject_.erase(MapObject_.begin(), MapObject_.end());


}


void MyFarmLevel::Update()
{
	
	//float4 NextPos = Player_->GetPosition() + (float4::RIGHT *GameEngineTime::GetDeltaTime() * 150.f);
	//float4 CheckPos = NextPos + float4(0.0f, 20.0f);
	//std::list<Items*>::iterator Iter;

	Time -= GameEngineTime::GetDeltaTime();



	if (0 >= Time)
	{
	//	BgmPlayer.Stop();
	}

	

}
