#include "PlayLevel.h"

#include "BotUI.h"


enum class ORDER
{
	//BACKGROUND,
	PLAYER,
	PLAYERHAIR,
	PLAYERPANTS,
	PLAYERSHIRTS,
	ENERGYFRAME,
	ENERGYBAR,
	MAINUI
};

PlayLevel::PlayLevel() 
	:
	Player_(nullptr),
	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	PlayerHair_(nullptr),
	PlayerShirts_(nullptr),
	PlayerPants_(nullptr)

{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{

}

void PlayLevel::LevelChangeStart()
{
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	PlayerHair_ = CreateActor<PlayerHair>((int)ORDER::PLAYERHAIR);
	PlayerPants_ = CreateActor<PlayerPants>((int)ORDER::PLAYERPANTS);
	PlayerShirts_ = CreateActor<PlayerShirts>((int)ORDER::PLAYERSHIRTS);

	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)ORDER::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)ORDER::ENERGYBAR);

}


void PlayLevel::Update()
{
	//플레이어가 행동 할때마다 스테미너 감소. 테스트용
	PlayerEnergyBar_->SubEnergyBar(Player_->GetEnergy());

	PlayerHair_->SetPosition(Player_->GetPosition());
	PlayerPants_->SetPosition(Player_->GetPosition());
	PlayerShirts_->SetPosition({ Player_->GetPosition().x, Player_->GetPosition().y+ 6.f }); // 6? (16/2)-2
}
