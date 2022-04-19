#pragma once
#include"PlayLevel.h"

class Player;
class Inventory;


// Ό³Έν :
class MyFarmLevel : public PlayLevel
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

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:
	void LoadMapObject();

	float Time;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;



	Player* MainPlayer;
	Inventory* MainInventory_;

};