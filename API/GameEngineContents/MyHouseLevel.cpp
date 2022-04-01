#include "MyHouseLevel.h"



enum class ORDER
{
	//BACKGROUND,
	PLAYER,

	ENERGYFRAME,
	ENERGYBAR,
	MAINUI
};

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
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)ORDER::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)ORDER::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)ORDER::MAINUI);

}

void MyHouseLevel::LevelChangeStart()
{


}


void MyHouseLevel::Update()
{
	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	//PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());





}
