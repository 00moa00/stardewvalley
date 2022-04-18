#include "MyFarmLevel.h"
#include "GameData.h"

#include "SmallStone.h"
#include "SmallWood1.h"
#include "SmallWood2.h"
#include "TreeTop.h"
#include "TreeBottom.h"

#include "PlayerHouse.h"
#include "Block.h"

#include "MoveHouse.h"
#include "MoveBusStop.h"
#include "MoveForest.h"
#include <GameEngineBase/GameEngineTime.h>

MyFarmLevel::MyFarmLevel()
	:
	Iter(MapObject_.begin())
	
{

	SetName("MyFarmLevel");
	

}

MyFarmLevel::~MyFarmLevel()
{

}

void MyFarmLevel::Loading()
{
	
}

void MyFarmLevel::LevelChangeStart()
{
	
	//if(MainInventory_ != nullptr) Inventory_ = MainInventory_;

	BackGroundFront_->GetRenderer()->SetImage("FarmFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("FarmBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

	BackGround_->DirtTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	BackGround_->WetTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });

	LoadMapObject();
	

	Player_->SetPosition({ FARM_SIZE_WEIGHT - 400.f, (FARM_SIZE_HEIGHT / 2) - 700.f });
	Player_->SetDirtTileMap(&BackGround_->DirtTileMap_);
	Player_->SetWetTileMap(&BackGround_->WetTileMap_);

	//BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	//Time = 5.0f;
}

void MyFarmLevel::LevelChangeEnd()
{
	//MainInventory_ = Inventory_;
}

void MyFarmLevel::LoadMapObject()
{

    char MapOject[FARM_CHIP_NUM_Y][FARM_CHIP_NUM_X] = {
    #include "Map/Farm.txt";

    };
	 

    for (int y = 0; y < FARM_CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < FARM_CHIP_NUM_X; x++)
        {
            const char chip = MapOject[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE + CHIP_SIZE * 0.5f,
                y * CHIP_SIZE + CHIP_SIZE,
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
				ThisIter->second->SetImageMapleBottom();
				ThisIter->second->SetPosition(pos);

				MapObject_.insert(std::make_pair(ChangeIndex - FARM_CHIP_NUM_Y, CreateActor<TreeTop>((int)PLAYLEVEL::TOP_OBJECT)));
				
				ThisIter = MapObject_.find(ChangeIndex - FARM_CHIP_NUM_Y);
				ThisIter->second->SetImageMapleTop();
				ThisIter->second->SetPosition({ pos.x , pos.y - 30.f });

				break;

			case FARM_TILE::FINE_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetImageFineBottom();
				ThisIter->second->SetPosition(pos);

				MapObject_.insert(std::make_pair(ChangeIndex - FARM_CHIP_NUM_Y, CreateActor<TreeTop>((int)PLAYLEVEL::TOP_OBJECT)));
				
				ThisIter = MapObject_.find(ChangeIndex - FARM_CHIP_NUM_Y);
				ThisIter->second->SetImageFineTop();
				ThisIter->second->SetPosition({ pos.x , pos.y - 30.f });


				break;

			case FARM_TILE::OAK_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetImageOakBottom();
				ThisIter->second->SetPosition(pos);

				MapObject_.insert(std::make_pair(ChangeIndex - FARM_CHIP_NUM_Y, CreateActor<TreeTop>((int)PLAYLEVEL::TOP_OBJECT)));
				
				ThisIter = MapObject_.find(ChangeIndex - FARM_CHIP_NUM_Y);
				ThisIter->second->SetImageOakTop();
				ThisIter->second->SetPosition({ pos.x , pos.y - 30.f });

				break;

			case FARM_TILE::MAHOGANI_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = MapObject_.find(ChangeIndex);
				ThisIter->second->SetImageMahoganyBottom();
				ThisIter->second->SetPosition(pos);

				MapObject_.insert(std::make_pair(ChangeIndex - FARM_CHIP_NUM_Y, CreateActor<TreeTop>((int)PLAYLEVEL::TOP_OBJECT)));
				
				ThisIter = MapObject_.find(ChangeIndex - FARM_CHIP_NUM_Y);
				ThisIter->second->SetImageMahoganyTop();
				ThisIter->second->SetPosition({ pos.x , pos.y - 30.f });


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

	Player_->CopyList(MapObject_);


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
