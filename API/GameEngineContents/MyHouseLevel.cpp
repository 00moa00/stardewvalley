#include "MyHouseLevel.h"
#include "GameData.h"

#include "Block.h"
#include "BadBottom.h"
#include "BadTop.h"
#include "Chair.h"
#include "Table.h"
#include "Tv.h"
#include "Hitter.h"
#include "MoveFarm.h"

#include <GameEngineBase/GameEngineTime.h>


MyHouseLevel::MyHouseLevel()
	:

	TileState_(TILE_COLL::INIT),
	MainUI_(nullptr),
	Player_(nullptr),
	Iter(MapObject_.begin())

{
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
{

	
	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	Player_->SetPosition({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y + 100.f });
	Player_->Renderer()->CameraEffectOff();

	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);


	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);

	BackGround_->GetRenderer()->SetImage("PlayerHouse.bmp");
	BackGround_->GetRenderer()->CameraEffectOff();
	BackGround_->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y});



	BgmPlayer = GameEngineSound::SoundPlayControl("05 - Spring (It's A Big World Outside).mp3");
	Time = 5.0f;


	LoadMapObject();
	//Inventory_->AllUpdateOff();
}

void MyHouseLevel::LevelChangeStart()
{

	BgmPlayer.Stop();


}

void MyHouseLevel::LoadMapObject()
{

    char MapOject[MYHOUSE_CHIP_NUM_Y][MYHOUSE_CHIP_NUM_X] = {
    #include "Map/FarmerHouse.txt";

    };
	 

    for (int y = 0; y < MYHOUSE_CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < MYHOUSE_CHIP_NUM_X; x++)
        {
            const char chip = MapOject[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE_F + CHIP_SIZE_F * 0.5f,
                y * CHIP_SIZE_F + CHIP_SIZE_F,
            };

			MYHOUSE_OBJECT_TILE TileState_ = static_cast<MYHOUSE_OBJECT_TILE>(chip);
			std::list<Items*>::iterator ThisIter;

			switch (TileState_)
			{
			case MYHOUSE_OBJECT_TILE::BAD_BOTTOM:
				MapObject_.push_back(CreateActor<BadBottom>((int)PLAYLEVEL::TOPOBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition({ pos.x, pos.y });
				MapObject_.push_back(CreateActor<BadTop>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition({ pos.x, pos.y });

				break;
			case MYHOUSE_OBJECT_TILE::TV:
				MapObject_.push_back(CreateActor<Tv>((int)PLAYLEVEL::OBJECT));
				

				break;
			case MYHOUSE_OBJECT_TILE::HITTER:
				MapObject_.push_back(CreateActor<Hitter>((int)PLAYLEVEL::OBJECT));

				break;
			case MYHOUSE_OBJECT_TILE::TABLE:
				MapObject_.push_back(CreateActor<Table>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->getRenderer()-> CameraEffectOff();

				break;
			case MYHOUSE_OBJECT_TILE::CHAIR:
				MapObject_.push_back(CreateActor<Chair>((int)PLAYLEVEL::OBJECT));

				break;
			case MYHOUSE_OBJECT_TILE::BLOCK:
				MapObject_.push_back(CreateActor<Block>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();

				(*ThisIter)->getRenderer()->CameraEffectOff();
				(*ThisIter)->getRenderer()->SetPivot({ 0, -24.f });
				(*ThisIter)->SetScale({ 48.f, 48.f + 48.f });

				break;
			case MYHOUSE_OBJECT_TILE::MOVEFARM:
				MapObject_.push_back(CreateActor<MoveFarm>((int)PLAYLEVEL::OBJECT));
				ThisIter = --MapObject_.end();
				(*ThisIter)->getRenderer()->CameraEffectOff();


			//	break;
			default:
				break;
			}

			ThisIter = --MapObject_.end();
			(*ThisIter)->SetPosition({ pos.x, pos.y });
			
     
        }
    }

}


void MyHouseLevel::Update()
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
			Player_->SetBreakY(false);

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
