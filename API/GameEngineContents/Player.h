#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	float GetEnergy() {
		return Energy_;
	}
	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:



	float Speed_;
	float Energy_;


	void Start() override;
	void Update() override;
	void Render() override;
};

