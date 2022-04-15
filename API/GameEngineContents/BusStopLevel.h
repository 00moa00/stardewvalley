#pragma once

#include "PlayLevel.h"


// Ό³Έν :
class BusStopLevel : public PlayLevel
{
public:
	// constrcuter destructer
	BusStopLevel();
	~BusStopLevel();

	// delete Function
	BusStopLevel(const BusStopLevel& _Other) = delete;
	BusStopLevel(BusStopLevel&& _Other) noexcept = delete;
	BusStopLevel& operator=(const BusStopLevel& _Other) = delete;
	BusStopLevel& operator=(BusStopLevel&& _Other) noexcept = delete;

protected:

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	void LoadMapObject();
	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;
};

