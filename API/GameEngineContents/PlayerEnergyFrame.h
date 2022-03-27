#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class PlayerEnergyFrame : public GameEngineActor
{
public:
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
	void Render() override;

private:

	float4 ImageScale_;

	GameEngineRenderer* PlayerEngergyFrame_;


};

