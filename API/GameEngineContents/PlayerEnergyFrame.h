#pragma once
#include <GameEngine/GameEngineActor.h>
#include "PlayerEnergyBar.h"

// Ό³Έν :
class PlayerEnergyFrame : public GameEngineActor
{
public:
	static PlayerEnergyFrame* MainPlayerEnergyFrame;
	static 	PlayerEnergyBar* MainPlayerEnergyBar;
	
	// constrcuter destructer
	PlayerEnergyFrame();
	~PlayerEnergyFrame();

	// delete Function
	PlayerEnergyFrame(const PlayerEnergyFrame& _Other) = delete;
	PlayerEnergyFrame(PlayerEnergyFrame&& _Other) noexcept = delete;
	PlayerEnergyFrame& operator=(const PlayerEnergyFrame& _Other) = delete;
	PlayerEnergyFrame& operator=(PlayerEnergyFrame&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	GameEngineRenderer* PlayerEngergyFrame_;

};

