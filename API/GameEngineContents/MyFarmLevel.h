#pragma once
#include"PlayLevel.h"

class Player;
class Inventory;


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

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:

	float Time;

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

private:
	void LoadMapObject();
};