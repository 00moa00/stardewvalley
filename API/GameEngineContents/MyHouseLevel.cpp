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
#include "GiftBox.h"

#include <GameEngineBase/GameEngineTime.h>


MyHouseLevel::MyHouseLevel()
	:
	//Iter(MapObject_.begin()),
	Time(0.f),
	MenuWaitTimer_(5.0f),

	GuideMoveState_(GUIDE_MOVE::MOVE_RIGHT),

	MenuGuide_(nullptr)

{

	SetName("MyHouseLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
	MenuGuide_ = CreateActor<BackGround>((int)PLAYLEVEL::ITEM);
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
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

	if (MapObject_.empty() == true)
	{
		LoadMapObject();
	}

	//Shop::MainShop->ShopOff();

}

void MyHouseLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	if (MenuGuide_ != nullptr)
	{
		MenuGuide_->GetRenderer()->SetImage("GameGuide.bmp");
		MenuGuide_->GetRenderer()->SetPivot({ 0 - 250 / 2,  GameEngineWindow::GetScale().Half().y });
		MenuGuide_->GetRenderer()->CameraEffectOff();

	}
	//	MenuGuide_->GetRenderer()->SetPivot({0 + 250/2,  GameEngineWindow::GetScale().Half().y });

	

	BackGroundFront_->GetRenderer()->SetImage("PlayerHouseFront.bmp");
	BackGroundFront_->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y });
	BackGroundFront_->GetRenderer()->CameraEffectOff();

	BackGround_->GetRenderer()->SetImage("PlayerHouse.bmp");
	BackGround_->GetRenderer()->CameraEffectOff();
	BackGround_->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y });

	//BackGround_->WetTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	//BackGround_->DirtTileMap_.TileRangeSetting(FARM_CHIP_NUM_X, FARM_CHIP_NUM_Y, { CHIP_SIZE, CHIP_SIZE });
	

	//Player::MainPlayer->Renderer()->CameraEffectOff();
	//Player::MainPlayer->SetDirtTileMap(&BackGround_->DirtTileMap_);
	//Player::MainPlayer->SetWetTileMap(&BackGround_->WetTileMap_);

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();

}

void MyHouseLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();

	}

}


void MyHouseLevel::LoadMapObject()
{

    char MapOject[MYHOUSE_CHIP_NUM_Y][MYHOUSE_CHIP_NUM_X] = {
	  #include "Map/FarmerHouse.txt"

    };
	 

    for (int y = 0; y < MYHOUSE_CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < MYHOUSE_CHIP_NUM_X; x++)
        {
            const char chip = MapOject[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE + CHIP_SIZE * 0.5f,
                y * CHIP_SIZE + CHIP_SIZE,
            };

			MYHOUSE_TILE TileState_ = static_cast<MYHOUSE_TILE>(chip);
			std::map<int, Items*>::iterator ThisIter;

			const float4 IndexPos = {
			  x * CHIP_SIZE ,
			  y * CHIP_SIZE,
			};

			TileIndex Index = { static_cast<int>(IndexPos.x / CHIP_SIZE), static_cast<int>(IndexPos.y / CHIP_SIZE) };
			int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);


			switch (TileState_)
			{
			case MYHOUSE_TILE::BAD_BOTTOM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<BadBottom>((int)PLAYLEVEL::TOP_OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition({ pos.x, pos.y });

				break;

			case MYHOUSE_TILE::GIFT:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<GiftBox>((int)PLAYLEVEL::OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->SetPosition({ pos.x, pos.y });

				break;

			case MYHOUSE_TILE::MOVE_FARM:

				MapObject_.insert(std::make_pair(ChangeIndex, CreateActor<MoveFarm>((int)PLAYLEVEL::TOP_OBJECT)));

				ThisIter = --MapObject_.end();
				ThisIter->second->GetRenderer()->CameraEffectOff();

				break;
			default:
				break;
			}

			ThisIter = --MapObject_.end();
			ThisIter->second->SetPosition(pos);

     
        }
    }

	Player::MainPlayer->CopyList(MapObject_);
	MapObject_.erase(MapObject_.begin(), MapObject_.end());

}

void MyHouseLevel::MoveGuide()
{

	static float4 CurrentPivot;

	switch (GuideMoveState_)
	{
	case GUIDE_MOVE::MOVE_RIGHT:

		CurrentPivot.x = MenuGuide_->GetRenderer()->GetPivot().x;
		CurrentPivot += float4::RIGHT * GameEngineTime::GetDeltaTime() * 60;

		MenuGuide_->GetRenderer()->SetPivot({ CurrentPivot.x,  GameEngineWindow::GetScale().Half().y });

		if (CurrentPivot.x > 0 + 250 / 2)
		{
			GuideMoveState_ = GUIDE_MOVE::WAIT;
		}

		break;
	case GUIDE_MOVE::WAIT:

		MenuGuide_->GetRenderer()->SetPivot({ 0 + 250 / 2,  GameEngineWindow::GetScale().Half().y });

		MenuWaitTimer_ -= GameEngineTime::GetDeltaTime();
		if (MenuWaitTimer_ < 0.f)
		{
			GuideMoveState_ = GUIDE_MOVE::MOVE_LEFT;
		}

		break;
	case GUIDE_MOVE::MOVE_LEFT:
		CurrentPivot.x = MenuGuide_->GetRenderer()->GetPivot().x;
		CurrentPivot += float4::LEFT * GameEngineTime::GetDeltaTime() * 60;

		MenuGuide_->GetRenderer()->SetPivot({ CurrentPivot.x,  GameEngineWindow::GetScale().Half().y });

		if (CurrentPivot.x < 0 - 250 / 2)
		{
			MenuGuide_->Death();
			GuideMoveState_ = GUIDE_MOVE::DEATH;
		}
		break;

	case GUIDE_MOVE::DEATH:
		MenuGuide_ = nullptr;

		break;
	default:
		break;
	}

}


void MyHouseLevel::Update()
{

	if (MenuGuide_ != nullptr)
	{
		MoveGuide();
	}


}



	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}

