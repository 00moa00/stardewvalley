#include "PlayLevel.h"

Player* PlayLevel::MainPlayer_ = nullptr;
Inventory* PlayLevel::MainInventory_ = nullptr;


PlayLevel::PlayLevel() 
	:
	PlayerEnergyBar_(nullptr),
	PlayerEnergyFrame_(nullptr),
	Player_(nullptr),
	TileState_(TILE_COLL::INIT),
	MainUI_(nullptr)
{

	Player_ = CreateActor<Player>((int)PLAYLEVEL::PLAYER);
	PlayerEnergyFrame_ = CreateActor<PlayerEnergyFrame>((int)PLAYLEVEL::ENERGYFRAME);
	PlayerEnergyBar_ = CreateActor<PlayerEnergyBar>((int)PLAYLEVEL::ENERGYBAR);
	MainUI_ = CreateActor<MainUI>((int)PLAYLEVEL::MAINUI);
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
	//Inventory_ = CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);

}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::LevelChangeEnd()
{


}

