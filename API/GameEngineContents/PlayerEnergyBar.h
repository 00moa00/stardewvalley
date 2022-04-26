#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class PlayerEnergyBar : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerEnergyBar();
	~PlayerEnergyBar();


	// delete Function
	PlayerEnergyBar(const PlayerEnergyBar& _Other) = delete;
	PlayerEnergyBar(PlayerEnergyBar&& _Other) noexcept = delete;
	PlayerEnergyBar& operator=(const PlayerEnergyBar& _Other) = delete;
	PlayerEnergyBar& operator=(PlayerEnergyBar&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	GameEngineRenderer* PlayerEngergyBar_;

public:
	GameEngineRenderer* GetRenderer()
	{
		return PlayerEngergyBar_;
	}

};

