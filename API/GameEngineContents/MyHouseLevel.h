#pragma once

#include "PlayLevel.h"



// Ό³Έν :
class MyHouseLevel : public PlayLevel
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
	void LevelChangeEnd() override;
private:

	void LoadMapObject();

	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;
};