#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayerBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerBackGround();
	~PlayerBackGround();

	// delete Function
	PlayerBackGround(const PlayerBackGround& _Other) = delete;
	PlayerBackGround(PlayerBackGround&& _Other) noexcept = delete;
	PlayerBackGround& operator=(const PlayerBackGround& _Other) = delete;
	PlayerBackGround& operator=(PlayerBackGround&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* PlayerBackGround_;

	void Start() override;
	void Update() override;
	void Render() override;
};

