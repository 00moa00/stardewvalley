#include "PlayLevel.h"
#include "BotUI.h"
#include "PlayerEnergyFrame.h"
#include "Player.h"
#include "PlayerEnergyBar.h"

enum class ORDER
{
	//BACKGROUND,
	PLAYER,
	ENERGYUI,
	MAINUI
};

PlayLevel::PlayLevel() 
	:
	Player_(nullptr),
	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr)
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
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)ORDER::ENERGYUI);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)ORDER::ENERGYUI);

}



void PlayLevel::Update()
{
	PlayerEnergyBar_->SubEnergyBar(Player_->GetEnergy());
}
