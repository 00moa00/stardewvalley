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

#include "MoveFlag.h"



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

	//if (nullptr == Shop::MainShop)
	//{
	//	Shop::MainShop = CreateActor<Shop>(static_cast<int>(PLAYLEVEL::SHOP));
	//}


}

void MyFarmLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}



	BackGroundFront_->GetRenderer()->SetImage("FarmFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("FarmBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });


	BackGround_->GetRenderer()->CameraEffectOn();

	FlowingFlower_ = CreateActor<FlowingFlower>(static_cast<int>(PLAYLEVEL::EFFECT));
	FlowingFlower_->SetMax({ FARM_SIZE_WEIGHT, FARM_SIZE_HEIGHT });

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();
	YSortOn(static_cast<int>(PLAYLEVEL::PLAYER));

	BackGround_->DirtTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	BackGround_->WetTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });

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
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
		PlayerHPFrame::MainPlayerHPFrame->NextLevelOn();


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

			TILE_LIST TileState_ = static_cast<TILE_LIST>(chip);
			std::map<int, Items*>::iterator ThisIter;


			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};


			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

			switch (TileState_)
			{
			case TILE_LIST::MAPLE_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetItemName("Maple_Tree");
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::FINE_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetItemName("Fine_Tree");
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::OAK_TREE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<TreeBottom>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetItemName("Oak_Tree");
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::SMALL_STONE:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::BIG_STONE:
				break;
			case TILE_LIST::SMALL_WOOD1:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallWood1>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::SMAA_WOOD2:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<SmallWood2>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				break;

			case TILE_LIST::MIDDLE_WOOD:
				break;
			case TILE_LIST::BIG_WOOD:
				break;
			case TILE_LIST::WEED1:
				break;
			case TILE_LIST::WEED2:
				break;

			case TILE_LIST::SHIPPING_BOX:
				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<ShippingBox>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				break;


			case TILE_LIST::MOVE_FOREST:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveBackForest");

				break;


			case TILE_LIST::MOVE_BUSSTOP:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveBusStop");

				break;

			case TILE_LIST::MOVE_HOUSE :

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFlag>((int)PLAYLEVEL::OBJECT)));
				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition(pos);
				ThisIter->second->CreateMoveFlag("MoveHouse");


				break;

		

			case TILE_LIST::BLOCK :

				break;
			default:
				break;
			
			}
			//ThisIter = MapObject_.find(ChangeIndex);
			//ThisIter->second->SetPosition(pos);
			
     
        }
    }


	Player::MainPlayer->CopyList(MapObject_);
//	MapObject_.erase(MapObject_.begin(), MapObject_.end());


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
