#pragma once

#include "PlayLevel.h"


// Ό³Έν :
class BusStopLevel : public GameEngineLevel
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
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

private:
	void LoadMapObject();

};

