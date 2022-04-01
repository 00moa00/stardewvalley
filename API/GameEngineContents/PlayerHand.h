#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class PlayerHand : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHand();
	PlayerHand(float _WalkAnimationFrame);

	~PlayerHand();

	GameEngineRenderer* Renderer() {
		return PlayerHand_;
	}

	// delete Function
	PlayerHand(const PlayerHand& _Other) = delete;
	PlayerHand(PlayerHand&& _Other) noexcept = delete;
	PlayerHand& operator=(const PlayerHand& _Other) = delete;
	PlayerHand& operator=(PlayerHand&& _Other) noexcept = delete;

protected:

private:

	float WalkAnimationFrame_;
	GameEngineRenderer* PlayerHand_;



	void Start() override;
	void Update() override;
	void Render() override;
};

