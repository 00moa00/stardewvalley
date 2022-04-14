#pragma once
#include <GameEngine/GameEngineLevel.h>

#include "TileData.h"


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
class MyHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MyHouseLevel();
	~MyHouseLevel();

	// delete Function
	MyHouseLevel(const MyHouseLevel& _Other) = delete;
	MyHouseLevel(MyHouseLevel&& _Other) noexcept = delete;
	MyHouseLevel& operator=(const MyHouseLevel& _Other) = delete;
	MyHouseLevel& operator=(MyHouseLevel&& _Other) noexcept = delete;
	
	float Time;

	GameEngineSoundPlayer BgmPlayer;

protected:

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

	void LoadMapObject();


	MainUI* MainUI_;
	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;

	TILE_COLL TileState_;
	Player* Player_;
	//Inventory* Inventory_;

	BackGround* BackGround_;

};