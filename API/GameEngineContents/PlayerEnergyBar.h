#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class PlayerEnergyBar : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerEnergyBar();
	~PlayerEnergyBar();

	void SubEnergyBar(float f) {
		EnergyBar_.y = f;
	}

	// delete Function
	PlayerEnergyBar(const PlayerEnergyBar& _Other) = delete;
	PlayerEnergyBar(PlayerEnergyBar&& _Other) noexcept = delete;
	PlayerEnergyBar& operator=(const PlayerEnergyBar& _Other) = delete;
	PlayerEnergyBar& operator=(PlayerEnergyBar&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;

private:




	float4 EnergyBar_;
	float4 ImageScale_;

	GameEngineRenderer* PlayerEngergyBar_;

};

