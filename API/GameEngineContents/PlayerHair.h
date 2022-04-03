#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayerHair : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHair();
	~PlayerHair();

	GameEngineRenderer* Renderer() {
		return PlayerHair_;
	}
	// delete Function
	PlayerHair(const PlayerHair& _Other) = delete;
	PlayerHair(PlayerHair&& _Other) noexcept = delete;
	PlayerHair& operator=(const PlayerHair& _Other) = delete;
	PlayerHair& operator=(PlayerHair&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* PlayerHair_;

	void Start() override;
	void Update() override;
	void Render() override;
};

