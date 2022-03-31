#include "MyHouseLevel.h"



enum class ORDER
{
	//BACKGROUND,
	PLAYER,
	PLAYERHAIR,
	PLAYERPANTS,
	PLAYERSHIRTS,
	PLAYERHAND,
	ENERGYFRAME,
	ENERGYBAR,
	MAINUI
};

MyHouseLevel::MyHouseLevel()
	:
	PlayerBody_(nullptr),
	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	PlayerHair_(nullptr),
	PlayerShirts_(nullptr),
	PlayerPants_(nullptr),
	MainUI_(nullptr)

{
}

MyHouseLevel::~MyHouseLevel()
{
}

void MyHouseLevel::Loading()
{
	PlayerBody_ = CreateActor<PlayerBody>((int)ORDER::PLAYER);
	PlayerHand_ = CreateActor<PlayerHand>((int)ORDER::PLAYERHAND);

	PlayerHair_ = CreateActor<PlayerHair>((int)ORDER::PLAYERHAIR);
	PlayerPants_ = CreateActor<PlayerPants>((int)ORDER::PLAYERPANTS);
	PlayerShirts_ = CreateActor<PlayerShirts>((int)ORDER::PLAYERSHIRTS);

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
	PlayerEnergyBar_->SubEnergyBar(PlayerBody_->GetEnergy());

	PlayerHair_->SetPosition(PlayerBody_->GetPosition());
	PlayerPants_->SetPosition(PlayerBody_->GetPosition());
	PlayerShirts_->SetPosition({ PlayerBody_->GetPosition().x, PlayerBody_->GetPosition().y + 11.f }); // 6? (16/2)-2
	PlayerHand_->SetPosition({ PlayerBody_->GetPosition().x, PlayerBody_->GetPosition().y });

	if (PlayerBody_->GetIsBackWalk()) {
		PlayerShirts_->SetBackWalk(true);
		PlayerHand_->SetBackWalk(true);
	}

	if (PlayerBody_->GetIsRightWalk()) {
		PlayerShirts_->setRightWalk(true);
		PlayerHand_->setRightWalk(true);

	}

	if (PlayerBody_->GetIsLeftWalk()) {
		PlayerShirts_->SetLeftWalk(true);
		PlayerHand_->SetLeftWalk(true);

	}
	if (PlayerBody_->GetIsFrontWalk()) {
		PlayerShirts_->SetFrontWalk(true);
		PlayerHand_->SetFrontWalk(true);

	}

	PlayerHand_->SetWalkInit(PlayerBody_->GetIsWalkInit());



}
