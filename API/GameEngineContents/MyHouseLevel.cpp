#include "MyHouseLevel.h"
#include "GameData.h"


MyHouseLevel::MyHouseLevel()
	:

	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),

	MainUI_(nullptr)

{
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
{

	
	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);

	LoadMapObject();
	//Inventory_->AllUpdateOff();
}

void MyHouseLevel::LevelChangeStart()
{
	BackGround_->GetRenderer()->SetImage("Farm.bmp");
	BackGround_->GetRenderer()->SetPivot({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_HEIGHT / 2 });

}

void MyHouseLevel::LoadMapObject()
{

    char st1_enemy[CHIP_NUM_Y][CHIP_NUM_X] = {
    #include "Map/Object_Tile Layer 2.txt";
   
    };


    for (int y = 0; y < CHIP_NUM_Y; y++)
    {
        for (int x = 0; x < CHIP_NUM_X; x++)
        {
            const char chip = st1_enemy[y][x];
            if (chip < 0) continue;

            const float4 pos = {
                x * CHIP_SIZE_F + CHIP_SIZE_F * 0.5f,
                y * CHIP_SIZE_F + CHIP_SIZE_F,
            };
         

			if (chip == 4) {

				//MapObject_.insert(std::make_pair( chip, CreateActor<SmallStone>((int)PLAYLEVEL::ITEM)));
				MapObject_.push_back(CreateActor<SmallStone>((int)PLAYLEVEL::OBJECT));
				std::list<Items*>::iterator ThisIter = --MapObject_.end();
				(*ThisIter)->SetPosition(pos);
			}

           
           // obj2dManager->add(enemy, enemyBehavior[chip], pos);
        }
    }

}


void MyHouseLevel::Update()
{


	
	float4 NextPos = Player_->GetPosition() + (float4::RIGHT *GameEngineTime::GetDeltaTime() * 150.f);
	float4 CheckPos = NextPos + float4(0.0f, 20.0f);



	std::list<Items*>::iterator Iter;


	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {
		if ((*Iter)->IsWall(Player_->GetPosition(), Player_->GetScale(), Player_->CurrentDir())) {
			Player_->SetSpeed(0.0f);
		}
		else {
			Player_->SetSpeed(150.0f);
		}

	}



	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}
}
