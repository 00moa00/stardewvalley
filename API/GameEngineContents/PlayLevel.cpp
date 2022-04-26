#include "PlayLevel.h"



PlayLevel::PlayLevel() 
		//PlayerEnergyBar_(nullptr),
	//PlayerEnergyFrame_(nullptr)
	//Player_(nullptr),
	//MainUI_(nullptr)
{

//	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	//PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	//PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
	//Inventory_ = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);

}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}


