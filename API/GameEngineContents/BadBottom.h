#pragma once
#include "Items.h"

// Ό³Έν :
class BadBottom : public Items
{
public:
	static BadBottom* MainBadBottom;

	// constrcuter destructer
	BadBottom();
	~BadBottom();

	// delete Function
	BadBottom(const BadBottom& _Other) = delete;
	BadBottom(BadBottom&& _Other) noexcept = delete;
	BadBottom& operator=(const BadBottom& _Other) = delete;
	BadBottom& operator=(BadBottom&& _Other) noexcept = delete;

private:

	void Start() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
};

