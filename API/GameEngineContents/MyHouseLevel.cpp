#include "MyHouseLevel.h"





MyHouseLevel::MyHouseLevel()
	:

	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),
	Inventory_(nullptr),
	MainUI_(nullptr),
	Mouse_(nullptr)
{
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
{
	Player_ = CreateActor<Player>((int)PlayLevel::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PlayLevel::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PlayLevel::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PlayLevel::MAINUI);
	CreateActor<TitleBackGround>((int)PlayLevel::BACKGROUND);
	Inventory_ = CreateActor<Inventory>((int)PlayLevel::PLAYER);
	Mouse_ = CreateActor<Mouse>((int)PlayLevel::MOUSE);
}

void MyHouseLevel::LevelChangeStart()
{


}


void MyHouseLevel::Update()
{
	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	////PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());
	//		if (GetAsyncKeyState(MK_LBUTTON))
	//{
	//	GameEngine::GetInst().ChangeLevel("Title");
	//}
}
