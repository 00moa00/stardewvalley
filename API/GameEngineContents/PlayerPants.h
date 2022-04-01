#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayerPants : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerPants();
	~PlayerPants();

	GameEngineRenderer* Renderer() {
		return PlayerPants_;
	}

	// delete Function
	PlayerPants(const PlayerPants& _Other) = delete;
	PlayerPants(PlayerPants&& _Other) noexcept = delete;
	PlayerPants& operator=(const PlayerPants& _Other) = delete;
	PlayerPants& operator=(PlayerPants&& _Other) noexcept = delete;

protected:

private:

	GameEngineRenderer* PlayerPants_;


	void Start() override;
	void Update() override;
	void Render() override;
};

