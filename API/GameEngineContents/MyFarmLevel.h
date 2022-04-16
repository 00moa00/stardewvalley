#pragma once
#include"PlayLevel.h"


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

	float Time;

	//GameEngineSoundPlayer BgmPlayer;


protected:

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	void LoadMapObject();


	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

};