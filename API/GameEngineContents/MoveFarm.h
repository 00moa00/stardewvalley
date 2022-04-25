#pragma once
#include "Items.h"
// Ό³Έν :
class MoveFarm : public Items
{
public:
	static MoveFarm* MainMoveFarm;

	// constrcuter destructer
	MoveFarm();
	~MoveFarm();

	// delete Function
	MoveFarm(const MoveFarm& _Other) = delete;
	MoveFarm(MoveFarm&& _Other) noexcept = delete;
	MoveFarm& operator=(const MoveFarm& _Other) = delete;
	MoveFarm& operator=(MoveFarm&& _Other) noexcept = delete;

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

};

