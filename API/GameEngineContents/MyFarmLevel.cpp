#include "MyFarmLevel.h"
#include "GameData.h"
#include "SmallStone.h"
#include "SmallWood1.h"
#include "SmallWood2.h"
#include "PlayerHouse.h"
#include "Block.h"



MyFarmLevel::MyFarmLevel()
	:

	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),
	TileState_(TILE_COLL::INIT),
	MainUI_(nullptr),
	Iter(MapObject_.begin())

{
}

MyFarmLevel::~MyFarmLevel()
{
}

void MyFarmLevel::Loading()
{

	
	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);

	LoadMapObject();
	//Inventory_->AllUpdateOff();
}

void MyFarmLevel::LevelChangeStart()
{
	BackGround_->GetRenderer()->SetImage("Farm.bmp");
	BackGround_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

}

void MyFarmLevel::LoadMapObject()
{

    char MapOject[CHIP_NUM_Y][CHIP_NUM_X] = {
    #include "Map/Farm.txt";

    };
	 

    for (int y = 0; y < CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < CHIP_NUM_X; x++)
        {
            const char chip = MapOject[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE_F + CHIP_SIZE_F * 0.5f,
                y * CHIP_SIZE_F + CHIP_SIZE_F,
            };

			OBJECT_TILE TileState_ = static_cast<OBJECT_TILE>(chip);
			std::list<Items*>::iterator ThisIter;

			switch (TileState_)
			{
			case OBJECT_TILE::MAPLE_TREE:
				break;
			case OBJECT_TILE::PINE_TREE:
				break;
			case OBJECT_TILE::OAK_TREE:
				break;
			case OBJECT_TILE::MAHOGANI_TREE:
				break;
			case OBJECT_TILE::SMALL_STONE:

				MapObject_.push_back(CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition(pos);

				break;
			case OBJECT_TILE::BIG_STONE:
				break;
			case OBJECT_TILE::SMALL_WOOD1:

				MapObject_.push_back(CreateActor<SmallWood1>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition(pos);

				break;
			case OBJECT_TILE::SMAA_WOOD2:
				MapObject_.push_back(CreateActor<SmallWood2>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition(pos);
				break;
			case OBJECT_TILE::MIDDLE_WOOD:
				break;
			case OBJECT_TILE::BIG_WOOD:
				break;
			case OBJECT_TILE::WEED1:
				break;
			case OBJECT_TILE::WEED2:
				break;

			case OBJECT_TILE::MY_HOUSE :

				MapObject_.push_back(CreateActor<PlayerHouse>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition(pos);
				break;

			case OBJECT_TILE::BLOCK :

				MapObject_.push_back(CreateActor<Block>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition(pos);
			default:
				break;
			
			}

			
     
        }
    }

}


void MyFarmLevel::Update()
{
	
	//float4 NextPos = Player_->GetPosition() + (float4::RIGHT *GameEngineTime::GetDeltaTime() * 150.f);
	//float4 CheckPos = NextPos + float4(0.0f, 20.0f);
	//std::list<Items*>::iterator Iter;


	switch (TileState_)
	{
	case TILE_COLL::INIT :
		Iter = MapObject_.begin();
		TileState_ = TILE_COLL::NOTACT;

	break;

	case TILE_COLL::NOTACT :
	

		for (; Iter != MapObject_.end(); ++Iter) {

			if ((*Iter)->IsWall(Player_->GetPosition(), Player_->GetScale(), Player_->CurrentDir()) == true) {
				Player_->SetSpeed(0.0f);
				TileState_ = TILE_COLL::COll;
				break;
			}


		}


		if (Iter == MapObject_.end()) {
			Iter = MapObject_.begin();
		}
		break;

	case TILE_COLL::COll:


		if ((*Iter)->IsWall(Player_->GetPosition(), Player_->GetScale(), Player_->CurrentDir())==false) {
			Player_->SetSpeed(150.f);

			Iter = MapObject_.begin();
			TileState_ = TILE_COLL::NOTACT;
		}

		break;
	}



	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}
}
