#pragma once
#include "Items.h"

// Ό³Έν :
class MoveSaloon : public Items
{
public:
	static MoveSaloon* MainMoveSaloon;

	// constrcuter destructer
	MoveSaloon();
	~MoveSaloon();

	// delete Function
	MoveSaloon(const MoveSaloon& _Other) = delete;
	MoveSaloon(MoveSaloon&& _Other) noexcept = delete;
	MoveSaloon& operator=(const MoveSaloon& _Other) = delete;
	MoveSaloon& operator=(MoveSaloon&& _Other) noexcept = delete;

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
};

