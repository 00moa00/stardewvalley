#pragma once
#include <GameEngine/GameEngineActor.h>




// Ό³Έν :
class PlayerBody : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerBody();
	PlayerBody(float _AnimationFrame);

	~PlayerBody();


	// delete Function
	PlayerBody(const PlayerBody& _Other) = delete;
	PlayerBody(PlayerBody&& _Other) noexcept = delete;
	PlayerBody& operator=(const PlayerBody& _Other) = delete;
	PlayerBody& operator=(PlayerBody&& _Other) noexcept = delete;

	GameEngineRenderer* Renderer() {
		return PlayerBody_;
	}

protected:

private:

	float WalkAnimationFrame_;
	GameEngineRenderer* PlayerBody_;


	void Start() override;
	void Update() override;
	void Render() override;
};

