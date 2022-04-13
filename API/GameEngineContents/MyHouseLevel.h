#pragma once
#include <GameEngine/GameEngineLevel.h>

#include "GameData.h"


#include "MainUI.h"
#include "BackGround.h"
#include "Player.h"

#include "RendererEnum.h"
#include "Inventory.h"
#include "Items.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>


#include <list>


enum class MYHOUSE_OBJECT_TILE {
	BAD_BOTTOM,
	BAD,
	TV,
	HITTER,
	TABLE,
	CHAIR,
	MOVE_FARM = 28,
	BLOCK = 29,

}; 

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

	BackGround* BackGround_;

};