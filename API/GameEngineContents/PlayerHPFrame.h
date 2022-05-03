#pragma once
#include "PlayerEnergyBar.h"

// Ό³Έν :
class PlayerHPFrame : public GameEngineActor
{
public:
	static PlayerHPFrame* MainPlayerHPFrame;
	static 	PlayerEnergyBar* MainPlayerHPBar;

	PlayerHPFrame();
	~PlayerHPFrame();

	// delete Function
	PlayerHPFrame(const PlayerHPFrame& _Other) = delete;
	PlayerHPFrame(PlayerHPFrame&& _Other) noexcept = delete;
	PlayerHPFrame& operator=(const PlayerHPFrame& _Other) = delete;
	PlayerHPFrame& operator=(PlayerHPFrame&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineRenderer* PlayerEngergyFrame_;

};

