#include "MyFarmLevel.h"
#include "GameData.h"

#include "SmallStone.h"
#include "SmallWood1.h"
#include "SmallWood2.h"
#include "PlayerHouse.h"
#include "Block.h"
#include "MoveHouse.h"

#include <GameEngineBase/GameEngineTime.h>

MyFarmLevel::MyFarmLevel()
	:

	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),
	TileState_(TILE_COLL::INIT),
	MainUI_(nullptr),
	Iter(MapObject_.begin())

{

	SetName("MyFarmLevel");

	//Inventory_ = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);

	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

MyFarmLevel::~MyFarmLevel()
{

}

void MyFarmLevel::Loading()
{
	
}

void MyFarmLevel::LevelChangeStart()
{
	
	BackGroundFront_->GetRenderer()->SetImage("FarmFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

	BackGround_->GetRenderer()->SetImage("FarmBack.bmp");
	BackGround_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });
	BackGround_->TileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });

	LoadMapObject();

	Player_->SetPosition({ FARM_SIZE_WEIGHT - 400.f, (FARM_SIZE_HEIGHT / 2) - 700.f });
	Player_->SetTileMap(&BackGround_->TileMap_);
	
	BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	Time = 5.0f;
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
			
				break;
			case OBJECT_TILE::BIG_STONE:
				break;
			case OBJECT_TILE::SMALL_WOOD1:

				MapObject_.push_back(CreateActor<SmallWood1>((int)PLAYLEVEL::OBJECT));
				
				break;
			case OBJECT_TILE::SMAA_WOOD2:
				MapObject_.push_back(CreateActor<SmallWood2>((int)PLAYLEVEL::OBJECT));
				
				break;
			case OBJECT_TILE::MIDDLE_WOOD:
				break;
			case OBJECT_TILE::BIG_WOOD:
				break;
			case OBJECT_TILE::WEED1:
				break;
			case OBJECT_TILE::WEED2:
				break;

			case OBJECT_TILE::MOVE_HOUSE :

				MapObject_.push_back(CreateActor<MoveHouse>((int)PLAYLEVEL::OBJECT));
				
				break;

			case OBJECT_TILE::BLOCK :

				//MapObject_.push_back(CreateActor<Block>((int)PLAYLEVEL::OBJECT));
				break;
			default:
				break;
			
			}
			ThisIter = --MapObject_.end();
			(*ThisIter)->SetPosition(pos);
			
     
        }
    }

}


void MyFarmLevel::Update()
{
	
	//float4 NextPos = Player_->GetPosition() + (float4::RIGHT *GameEngineTime::GetDeltaTime() * 150.f);
	//float4 CheckPos = NextPos + float4(0.0f, 20.0f);
	//std::list<Items*>::iterator Iter;

	Time -= GameEngineTime::GetDeltaTime();



	if (0 >= Time)
	{
		BgmPlayer.Stop();
	}

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


		/*if (true == GameEngineInput::GetInst()->IsPress("MoveRight") && true == GameEngineInput::GetInst()->IsPress("MoveDown")) {
			TileState_ = TILE_COLL::RIGHTDOWN; }
		


		if (true == GameEngineInput::GetInst()->IsPress("MoveRight") && true == GameEngineInput::GetInst()->IsPress("MoveUp")) {
			TileState_ = TILE_COLL::RIGHTUP;
		}


		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") && true == GameEngineInput::GetInst()->IsPress("MoveDown")) {
			TileState_ = TILE_COLL::LEFTDOWN;
		}



		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") && true == GameEngineInput::GetInst()->IsPress("MoveUp")) {
			TileState_ = TILE_COLL::LEFTUP;
		}

*/


		if ((*Iter)->IsWall(Player_->GetPosition(), Player_->GetScale(), Player_->CurrentDir())==false) {
			Player_->SetSpeed(150.f);
			//Player_->SetBreakY(false);

			Iter = MapObject_.begin();
			TileState_ = TILE_COLL::NOTACT;
		}

		break;


	//case TILE_COLL::RIGHTDOWN:

	//	Player_->SetBreakY(true);
	//	if ((true == GameEngineInput::GetInst()->IsFree("MoveDown")) && (Player_->GetBreakY())) {

	//		Player_->SetBreakY(false);
	//		TileState_ = TILE_COLL::COll;
	//	}

	//	
	//	break;
	//case TILE_COLL::RIGHTUP:

	//	Player_->SetBreakY(true);
	//	if ((true == GameEngineInput::GetInst()->IsFree("MoveUp")) && (Player_->GetBreakY())) {

	//		Player_->SetBreakY(false);
	//		TileState_ = TILE_COLL::COll;
	//	}


	//	break;




	//case TILE_COLL::LEFTDOWN:

	//	Player_->SetBreakY(true);
	//	if ((true == GameEngineInput::GetInst()->IsFree("MoveDown")) && (Player_->GetBreakY())) {

	//		Player_->SetBreakY(false);
	//		TileState_ = TILE_COLL::COll;
	//	}


	//case TILE_COLL::LEFTUP:


	//	Player_->SetBreakY(true);
	//	if ((true == GameEngineInput::GetInst()->IsFree("MoveUp")) && (Player_->GetBreakY())) {

	//		Player_->SetBreakY(false);
	//		TileState_ = TILE_COLL::COll;
	//	}

	}



	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}
}
