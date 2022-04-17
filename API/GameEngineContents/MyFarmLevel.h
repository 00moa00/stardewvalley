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

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;


protected:



private:
	void LoadMapObject();

	float Time;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

};