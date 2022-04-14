#pragma once
#include <GameEngine/GameEngineLevel.h>

#include "TileData.h"

#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "BackGround.h"
#include "Player.h"

#include "RendererData.h"
#include "Inventory.h"
#include "Items.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>


#include <list>




// Ό³Έν :
class MyFarmLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MyFarmLevel();
	~MyFarmLevel();

	// delete Function
	MyFarmLevel(const MyFarmLevel& _Other) = delete;
	MyFarmLevel(MyFarmLevel&& _Other) noexcept = delete;
	MyFarmLevel& operator=(const MyFarmLevel& _Other) = delete;
	MyFarmLevel& operator=(MyFarmLevel&& _Other) noexcept = delete;

	float Time;

	GameEngineSoundPlayer BgmPlayer;


protected:

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
//	void LevelChangeEnd() override;

private:

	void LoadMapObject();


	MainUI* MainUI_;
	//std::map<int, Items*> MapObject_;
	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;

	TILE_COLL TileState_;
	Player* Player_;
	//Inventory* Inventory_;
	PlayerEnergyBar* PlayerEnergyBar_;
	PlayerEnergyFrame* PlayerEnergyFrame_;
	BackGround* BackGround_;
	BackGround* BackGroundFront_;

};