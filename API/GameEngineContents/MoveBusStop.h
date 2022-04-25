#pragma once
#include "Items.h"
// Ό³Έν :
class MoveBusStop : public Items
{
public:
	static MoveBusStop* MainMoveBusStop;

	// constrcuter destructer
	MoveBusStop();
	~MoveBusStop();

	// delete Function
	MoveBusStop(const MoveBusStop& _Other) = delete;
	MoveBusStop(MoveBusStop&& _Other) noexcept = delete;
	MoveBusStop& operator=(const MoveBusStop& _Other) = delete;
	MoveBusStop& operator=(MoveBusStop&& _Other) noexcept = delete;

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};

